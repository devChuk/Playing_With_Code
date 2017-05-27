/*
Brian Chuk (brianch.uk)
Message me on my website and say hello! :)
Or tweet or email at me
*/

////////////////////////////////////////SETUP////////////////////////////////////////

// ThreeJS variables
var vw = window.innerWidth;
var vh = window.innerHeight;
var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 75, vw/vh, 0.1, 1000 );
var renderer = new THREE.WebGLRenderer({antialias: true});
camera.position.z = 655;
var closeEnough = 130;
var finalcloseEnough = 10;

// HTML Canvas variables
var canvas;

// Runtime values
var startTime;
var STAGE = {
    TRANSITION: 0,
    SPHERE: 1,
    STARFIELD: 2,
    STAG: 3
};

// Runtime generated models
var sphereM;
var starFieldM = [];            // contains vertices of a randomized starfield
var starVelocities = [];        // contains velocities of said starfield

// Blender 3D models
var sBorderM;                   // (the s stands for stag. Which means yung male deer)
var sEyeM;
var sEarLM;
var sEarRM;
var sSnoutM;

var sBorderV = [];
var sEyeV = [];
var sEarLV = [];
var sEarRV = [];
var sSnoutV = [];

// TRANSITION VALUES
var _stage = STAGE.SPHERE;      // keeps track of current stage
var vertices;                   // contains all the vertices to render
var _distanceTravelled;         // records distance travelled for each vertex during transitions
var _goalPoints;                // contains the destinations of each vertex after transitions
var _goalMovements;             // contains directions used for transitions for each vertex
var _goalPointsSatisfied;       // contains status of transition completion for each vertex
var _speeds;                    // contains the speeds of each vertex during transitions. Ideally for Material Design
var _newStage;                  // contains the goal stage
var _sFadeIn = 0;               // fades in stag connections
var _sGoalDistance = [];        //stores the goal distances of the stag border vertices

// Triangulation magic
var baseTriangles = [];

// var baseTriangles = {
//     vertices: [],
//     areaRatios: []
// };
var leftEarTriangles = {
    vertices: [],
    areaRatios: []
};
var rightEarTriangles = {
    vertices: [],
    areaRatios: []
};


////////////////////////////////////////HELPER FUNCTIONS/////////////////////////////

function p(num) {return Math.pow(num, 2);}
function sqrt(num) {return Math.sqrt(num);}
function map_range(value, low1, high1, low2, high2) {return (low2 + (high2 - low2) * (value - low1) / (high1 - low1));}
function reset() {this.scene = new THREE.Scene(); setup();}
function distanceBetweenDimTwo(p1, p2) {return sqrt(p(p1.x - p2.x) + p(p1.y - p2.y));}

window.addEventListener('resize', onWindowResize, false);
function onWindowResize(){
    vw = window.innerWidth; vh = window.innerHeight;
    camera.aspect = vw / vh;
    camera.updateProjectionMatrix();
    renderer.setSize( vw, vh );
    reset();
}

function projectToScreen(threeDimPoint){
    var point = threeDimPoint.clone();
    var winWidthHalf = (document.documentElement.clientWidth/2);
    var winHeightHalf = (document.documentElement.clientHeight/2);
    point.project(camera);
    point.x = ( point.x * winWidthHalf ) + winWidthHalf;
    point.y = - ( point.y * winHeightHalf ) + winHeightHalf;
    point.z = 0;
    return point;
};

function projectModelVertices(mesh) {
    var startIndex = vertices.length;

    for (var i = 0; i < mesh.geometry.vertices.length; i++) {
        vertices.push(mesh.geometry.vertices[i].clone());
        vertices[i + startIndex].applyMatrix4(mesh.matrixWorld);
        vertices[i + startIndex] = projectToScreen(vertices[i + startIndex]);
    }
}

function genProjectedVertices(model, projectedVertices) {
    model.updateMatrixWorld();

    for (var i = 0; i < model.geometry.vertices.length; i++) {
        var b = model.geometry.vertices[i].clone();
        b.applyMatrix4(model.matrixWorld);
        b = projectToScreen(b);
        projectedVertices.push(b);
    }
}

function drawConnections(distanceThreshold, ctx) {
    for (var i = 0; i < vertices.length; i++) {
        for (var j = i + 1; j < vertices.length; j++) {
            var dist = distanceBetweenDimTwo(vertices[i], vertices[j]);
            if (dist < distanceThreshold) {
                ctx.strokeStyle = '#ffffff';
                ctx.globalAlpha = map_range(dist, 0, distanceThreshold, 0.5, 0);
                ctx.beginPath();
                ctx.moveTo(vertices[i].x, vertices[i].y);
                ctx.lineTo(vertices[j].x, vertices[j].y);
                ctx.stroke();
            }
        }
    }
}

function genRandPtOutsideScreen(array, flag) {
    var perimeter = (canvas.width+ canvas.height) * 2;
    var LEFT = flag != null && flag.indexOf("LEFT") !== -1;
    var RIGHT = flag != null && flag.indexOf("RIGHT") !== -1;
    var ptLoc;
    var maxDistFromScreenEdge = 250;

    if (LEFT) {
        ptLoc = Math.random() * canvas.height;
    } else if (RIGHT) {
        ptLoc = Math.random() * canvas.height + canvas.width + canvas.height;
    } else {
        ptLoc = Math.random() * perimeter;
    }

    if (LEFT || (0 < ptLoc && ptLoc < canvas.height)) {
        array.push({
            x: Math.random() * -maxDistFromScreenEdge,
            y: ptLoc
        });
    } else if (canvas.height < ptLoc && ptLoc < canvas.height + canvas.width) {
        array.push({
            x: ptLoc - canvas.height,
            y: canvas.height + Math.random() * maxDistFromScreenEdge
        });
    } else if (RIGHT || (ptLoc < canvas.height * 2 + canvas.width && ptLoc > canvas.height + canvas.width)) {
        array.push({
            x: canvas.width + Math.random() * maxDistFromScreenEdge,
            y: ptLoc - canvas.height - canvas.width
        });
    } else {
        array.push({
            x: ptLoc - canvas.height * 2 - canvas.width,
            y: Math.random() * -maxDistFromScreenEdge
        });
    }
}

function triangulate(arrayOfVertices, holeMeshes) {
    var flattenedArray = [];

    for (var i = 0; i < arrayOfVertices.length; i++) {
        flattenedArray.push(arrayOfVertices[i].x);
        flattenedArray.push(arrayOfVertices[i].y);
    }

    var holeIndexes = [];

    if (holeMeshes) {
        for (var i = 0; i < holeMeshes.length; i++) {
            holeIndexes.push(flattenedArray.length / 2);

            for (var j = 0; j < holeMeshes[i].geometry.vertices.length; j++) {
                var b = holeMeshes[i].geometry.vertices[j].clone();
                b.applyMatrix4(holeMeshes[i].matrixWorld);
                b = projectToScreen(b);
                flattenedArray.push(b.x);
                flattenedArray.push(b.y);
            }
        }
    }

    return earcut(flattenedArray, holeIndexes);
}

// function generateTriangles() {

// }

////////////////////////////////////////RUNTIME FUNCTIONS////////////////////////////

function initMeshes() {
    var loader = new THREE.JSONLoader();
    sphereM = new THREE.Mesh(new THREE.SphereGeometry(300, 15, 15));

    var numStars = (canvas.width * canvas.height > 550000) ? 500 : 256;

    for (var i = 0; i < numStars; i++) {
        starFieldM.push({
            x: (Math.random() * canvas.width),
            y: (Math.random() * canvas.height)
        });
        starVelocities.push({
            dx: Math.random() * 0.4 - 0.2,
            dy: Math.random() * 0.4 - 0.2
        });
    }

    // model deets:
    // model2       ellipsoid
    // model3       cube
    // model        some flat random shape
    // sampleModel  building prisms
    // test         this is pretty arbitrary
    // test1        currently a stagborder.

    var stagScale = 200;
    loader.load('./res/models/sBorder.json', function(geometry) {sBorderM = new THREE.Mesh(geometry);sBorderM.scale.x = sBorderM.scale.y = stagScale;});
    loader.load('./res/models/sEye.json', function(geometry) {sEyeM = new THREE.Mesh(geometry);sEyeM.scale.x = sEyeM.scale.y = stagScale;});
    loader.load('./res/models/sEarL.json', function(geometry) {sEarLM = new THREE.Mesh(geometry);sEarLM.scale.x = sEarLM.scale.y = stagScale;});
    loader.load('./res/models/sEarR.json', function(geometry) {sEarRM = new THREE.Mesh(geometry);sEarRM.scale.x = sEarRM.scale.y = stagScale;});
    loader.load('./res/models/sSnout.json', function(geometry) {sSnoutM = new THREE.Mesh(geometry);sSnoutM.scale.x = sSnoutM.scale.y = stagScale;});
}

function startTransition(newStage) {
    _goalPointsSatisfied = [];
    _distanceTravelled = [];
    _goalPoints = [];

    switch(newStage) {
        case STAGE.STARFIELD:

            _goalPoints = starFieldM;
            for (var i = 0; i < 250; i++) {
                _distanceTravelled.push(0);
            }

            if (vertices.length < starFieldM.length) {
                vertices.length = 250;

                for (var i = 250; i < starFieldM.length; i++) {
                    genRandPtOutsideScreen(vertices, "LEFT");
                    _distanceTravelled.push(0);
                }
            }
            break;

        case STAGE.STAG:
            sBorderM.updateMatrixWorld();
            genProjectedVertices(sBorderM, sBorderV);
            sEyeM.updateMatrixWorld();
            genProjectedVertices(sEyeM, sEyeV);
            sEarLM.updateMatrixWorld();
            genProjectedVertices(sEarLM, sEarLV);
            sEarRM.updateMatrixWorld();
            genProjectedVertices(sEarRM, sEarRV);
            sSnoutM.updateMatrixWorld();
            genProjectedVertices(sSnoutM, sSnoutV);

            for (var i = 0; i < starFieldM.length; i++) {
                if (i < sBorderV.length) {
                    _goalPoints.push(sBorderV[i]);
                    if (i >= 1) {
                        _sGoalDistance.push(distanceBetweenDimTwo(
                            _goalPoints[i-1],
                            _goalPoints[i]
                        ));
                    }
                } else {
                    genRandPtOutsideScreen(_goalPoints, "RIGHT");
                }
                _distanceTravelled.push(0);
            }
            break;

    }
    for (var i = 0; i < _goalPoints.length; i++)
        _goalPointsSatisfied.push(false);
    if (_goalPoints.length < vertices.length) {
        vertices.length = _goalPoints.length;
    }
    _stage = STAGE.TRANSITION;
    _newStage = newStage;
    transitionTo(newStage, _goalPoints);
}

function transitionTo(newStage) {
    var transitionComplete = true;
    _goalMovements = [];
    _speeds = [];
    for (var i = 0; i < vertices.length; i++) {
        var diffX = _goalPoints[i].x - vertices[i].x;
        var diffY = _goalPoints[i].y - vertices[i].y;
        var magnitude = sqrt(p(diffX) + p(diffY));
        // (progress == 1) => trip is 100% complete
        var progress = _distanceTravelled[i] / (magnitude + _distanceTravelled[i]);
        var markerOne = 0.3;
        var markerTwo = 0.4;
        var speed = 0;
        var SKIP_SPEEDUP = false;
        var SKIP_SLOWDOWN = false;
        
        if (newStage === STAGE.STARFIELD && i >= 250) {
            SKIP_SPEEDUP = true;
        } else if (newStage === STAGE.STAG && i >= sBorderV.length) {
            SKIP_SLOWDOWN = true;
        }
        
        if (progress < markerOne && !SKIP_SPEEDUP) {
            speed = map_range(progress, 0, markerOne, 0.5, 20);
        } else if (progress <= markerTwo) {
            speed = 20;
        } else if (progress >= markerTwo && !SKIP_SLOWDOWN) {
            speed = map_range(progress, markerTwo, 1, 20, 3);
        } else {
            speed = 20;
        }
        _goalMovements.push({dx: diffX/magnitude * speed,
                             dy: diffY/magnitude * speed});
        _distanceTravelled[i] += speed;
        _speeds.push(speed);
    }
    for (var i = 0; i < vertices.length; i++) {
        if (_goalPointsSatisfied[i] == false) {
            transitionComplete = false;

            if (sqrt(p(_goalPoints[i].x - vertices[i].x) + p(_goalPoints[i].y - vertices[i].y)) > _speeds[i]) {
                vertices[i].x += _goalMovements[i].dx;
                vertices[i].y += _goalMovements[i].dy;
            } else {
                _goalPointsSatisfied[i] = true;
                vertices[i].x = _goalPoints[i].x;
                vertices[i].y = _goalPoints[i].y;
            }
        } else if (_goalPointsSatisfied[i] == true) {
            vertices[i].x = _goalPoints[i].x;
            vertices[i].y = _goalPoints[i].y;
        }
    }
    var closeEnoughChange = true;
    if (newStage == STAGE.STAG && closeEnough > finalcloseEnough)
        closeEnoughChange = false;
    if (transitionComplete && closeEnoughChange) {
        _stage = newStage;

        switch(newStage) {
            case STAGE.STARFIELD:
                sphereM.geometry.dispose();
                sphereM.material.dispose();
                sphereM = undefined;
            break;

            case STAGE.STAG:
                starFieldM = undefined;
                starVelocities = undefined;
                _distanceTravelled = undefined;
                _goalPoints = undefined;
                _goalMovements = undefined;
                _goalPointsSatisfied = undefined;
                _speeds = undefined;
                _newStage = undefined;
                _sFadeIn = undefined;
                _sGoalDistance = undefined;
            break;

        }
    }
}

function renderTransitions(ctx) {
    switch(_newStage) {
        case STAGE.STARFIELD:
            for (var i = 0; i < starFieldM.length; i++) {
                starFieldM[i].x += starVelocities[i].dx;
                starFieldM[i].y += starVelocities[i].dy;
                if (starFieldM[i].x < 0 || starFieldM[i].x > canvas.width)
                    starVelocities[i].dx *= -1;
                if (starFieldM[i].y < 0 || starFieldM[i].y > canvas.height)
                    starVelocities[i].dy *= -1;
                _goalPoints[i] = starFieldM[i];
            }
            break;

        case STAGE.STAG:
            for (var i = 0; i < sBorderV.length; i++) {
                _goalPoints[i] = sBorderV[i];
                if (i < sBorderV.length - 1) {
                    var dist = distanceBetweenDimTwo(vertices[i], vertices[i+1]);
                    if (dist < 70 || dist < _sGoalDistance[i] * 1.001) {
                        ctx.globalAlpha = map_range(dist, 0, 18, 0.8, 0.1) * _sFadeIn;
                        ctx.beginPath();
                        ctx.moveTo(vertices[i].x, vertices[i].y);
                        ctx.lineTo(vertices[i+1].x, vertices[i+1].y);
                        ctx.strokeStyle = '#ffffff';
                        ctx.stroke();
                    }
                }
            }
            // for (var i = 0; i < sBorderM.geometry.vertices.length; i++) {
            //     _goalPoints[i] = sBorderM.geometry.vertices[i].clone();
            //     _goalPoints[i].applyMatrix4(sBorderM.matrixWorld);
            //     _goalPoints[i] = projectToScreen(_goalPoints[i]);
            //     if (i < sBorderM.geometry.vertices.length - 1) {
            //         var dist = distanceBetweenDimTwo(vertices[i], vertices[i+1]);
            //         if (dist < 70 || dist < _sGoalDistance[i] * 1.001) {
            //             ctx.globalAlpha = map_range(dist, 0, 18, 0.8, 0.1) * _sFadeIn;
            //             ctx.beginPath();
            //             ctx.moveTo(vertices[i].x, vertices[i].y);
            //             ctx.lineTo(vertices[i+1].x, vertices[i+1].y);
            //             ctx.strokeStyle = '#ffffff';
            //             ctx.stroke();
            //         }
            //     }
            // }
            if (closeEnough > finalcloseEnough)
                closeEnough -= 0.5;
            if (_sFadeIn <= 1 && closeEnough <= finalcloseEnough + 50)
                _sFadeIn += 0.01;
            break;
    }
    transitionTo(_newStage);
    drawConnections(closeEnough, ctx);
}

function renderSphere(ctx) {
    sphereM.updateMatrixWorld();
    sphereM.rotation.x += 0.001;
    sphereM.rotation.y += 0.001;
    sphereM.rotation.z += 0.001;
    vertices = [];
    // projectModelVertices(sphereM);
    genProjectedVertices(sphereM, vertices);
    drawConnections(closeEnough, ctx);
}

function renderStarfield(ctx) {
    vertices = [];
    for (var i = 0; i < starFieldM.length; i++) {
        starFieldM[i].x += starVelocities[i].dx;
        starFieldM[i].y += starVelocities[i].dy;
        if (starFieldM[i].x < 0 || starFieldM[i].x > canvas.width)
            starVelocities[i].dx *= -1;
        if (starFieldM[i].y < 0 || starFieldM[i].y > canvas.height)
            starVelocities[i].dy *= -1;
        vertices.push(starFieldM[i]);
    }
    drawConnections(closeEnough, ctx);
}

function renderStag(ctx) {
    // CLEAN THIS FUNCTION
    sBorderM.updateMatrixWorld();
    sEyeM.updateMatrixWorld();
    sEarLM.updateMatrixWorld();
    sEarRM.updateMatrixWorld();
    sSnoutM.updateMatrixWorld();

    vertices = [];
    projectModelVertices(sBorderM);

    if (baseTriangles.length == 0) {
        baseTriangles = triangulate(vertices, [sEyeM, sSnoutM]);
        triangleColors = [];
        for (var i = 0; i < 383; i++) {
            triangleColors.push('hsl(' + 360 * Math.random() + ', 50%, 50%)');
        }
    }

    for (var i = 0; i < sEyeM.geometry.vertices.length; i++) {
        var b = sEyeM.geometry.vertices[i].clone();
        b.applyMatrix4(sEyeM.matrixWorld);
        b = projectToScreen(b);
        vertices.push(b);
    }

    for (var i = 0; i < sSnoutM.geometry.vertices.length; i++) {
        var b = sSnoutM.geometry.vertices[i].clone();
        b.applyMatrix4(sSnoutM.matrixWorld);
        b = projectToScreen(b);
        vertices.push(b);
    }


    for (var i = 0; i < baseTriangles.length; i += 3) {
        ctx.fillStyle = triangleColors[i];//'hsl(' + 360 * Math.random() + ', 50%, 50%)';
        ctx.globalAlpha = 1;
        ctx.beginPath();
        ctx.moveTo(vertices[baseTriangles[i]].x, vertices[baseTriangles[i]].y);
        ctx.lineTo(vertices[baseTriangles[i+1]].x, vertices[baseTriangles[i+1]].y);
        ctx.lineTo(vertices[baseTriangles[i+2]].x, vertices[baseTriangles[i+2]].y);
        // ctx.fillRect(baseTriangles[i].x, baseTriangles[i].y, 1, 1);
        ctx.closePath();
        ctx.fill();
        ctx.strokeStyle = '#ffff00';
        ctx.stroke();
    }

    ctx.fillStyle = "#f00"//"#1b1b19"
    tempFill(ctx, sEarLM);
    tempFill(ctx, sEarRM);

    for (var i = 0; i < vertices.length - 1; i++) {
        var dist = distanceBetweenDimTwo(vertices[i], vertices[i+1]);
        ctx.globalAlpha = map_range(dist, 0, 18, 0.8, 0.1);
        ctx.beginPath();
        ctx.moveTo(vertices[i].x, vertices[i].y);
        ctx.lineTo(vertices[i+1].x, vertices[i+1].y);
        ctx.strokeStyle = '#ffffff';
        ctx.stroke();
    }
}

////////////////////////////////////////CREATING OBJECTS/////////////////////////////

var setup = function () {
    renderer.setSize( vw, vh );
    container = document.createElement( 'div' );
    document.body.appendChild( container );
    canvas = document.getElementById("twoDimCanvas");
    canvas.width = vw;
    canvas.height = vh;
    stats = new Stats();                    //Generate FPS counter
    container.appendChild( stats.dom );
    starFieldM = [];
    starVelocities = [];
    initMeshes();
}

////////////////////////////////////////RENDERING & ANIMATING/////////////////////////

var render = function () {
    window.requestAnimationFrame( render );
    stats.update();    //Update FPS counter.
    var ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    switch(_stage) {
        case STAGE.TRANSITION:
            renderTransitions(ctx);
            break;

        case STAGE.SPHERE:
            renderSphere(ctx);
            break;

        case STAGE.STARFIELD:
            renderStarfield(ctx)
            break;

        case STAGE.STAG:
            renderStag(ctx);
            break;
    }

    var timeElapsed = Date.now() - startTime;                       //8000, 18000.   1000, 5000
    if (timeElapsed > 2000 && _stage == STAGE.SPHERE)
        startTransition(STAGE.STARFIELD);
    else if (timeElapsed > 7000 && _stage == STAGE.STARFIELD)
        startTransition(STAGE.STAG);
    renderer.render(scene, camera);
};

function tempFill(ctx, model) {
    ctx.beginPath();
    for (var i = 0; i < model.geometry.vertices.length; i++) {
        var b = model.geometry.vertices[i].clone();
        b.applyMatrix4(model.matrixWorld);
        var b = projectToScreen(b);
        ctx.lineTo(b.x, b.y);
        // ctx.fillRect(b.x, b.y, 1, 1);
    }
    ctx.closePath();
    ctx.fill();
}

////////////////////////////////////////RUN/////////////////////////

// THREE.DefaultLoadingManager.onProgress = function ( item, loaded, total ) {
//     console.log(item, loaded, total);
// };

THREE.DefaultLoadingManager.onLoad = function() {
    startTime = Date.parse(new Date());
    // generateTriangles();

    render();
}

setup();