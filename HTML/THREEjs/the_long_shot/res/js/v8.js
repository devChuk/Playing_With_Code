/*
Brian Chuk (brianch.uk)
Message me on my website and say hello! :)
*/

////////////////////////////////////////SETUP////////////////////////////////////////

// ThreeJS variables
var vw = window.innerWidth;
var vh = window.innerHeight;
var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 75, vw/vh, 0.1, 1000 );
var modelCanvas = document.getElementById("3d");
var renderer = new THREE.WebGLRenderer({antialias: true,
                                        canvas: modelCanvas});
camera.position.z = 655;
var closeEnough = 130;

// HTML Canvas variables
var canvas;
var starCloseEnough;

// Runtime values
var startTime;
var timeElapsed;
var STAGE = {
    TRANSITION: 0,
    SPHERE: 1,
    STARFIELD: 2,
    STAG: 3
};

// TRANSITION VALUES
var _stage = STAGE.SPHERE;      // keeps track of current stage
var vertices;                   // contains all the vertices to render
var _distanceTravelled;         // records distance travelled for each vertex during transitions
var _goalPoints;                // contains the destinations of each vertex after transitions
var _goalMovements;             // contains directions used for transitions for each vertex
var _goalPointsSatisfied;       // contains status of transition completion for each vertex
var _speeds;                    // contains the speeds of each vertex during transitions. Ideally for Material Design
var _newStage;                  // contains the goal stage
var transitionSpeed = 0.5;

// Blender 3D models
var sBorderM;                   // (the s stands for stag. Which means yung male deer)
var sEarM;
var sEyeM;
var sSnoutM;
var sFadeM;

// Runtime generated models
var sphereM;
var starFieldM = [];            // contains vertices of a randomized starfield
var starVelocities = [];        // contains velocities of said starfield



////////////////////////////////////////HELPER FUNCTIONS/////////////////////////////

function p(num) {return Math.pow(num, 2);}
function sqrt(num) {return Math.sqrt(num);}
function map_range(value, low1, high1, low2, high2) {return (low2 + (high2 - low2) * (value - low1) / (high1 - low1));}

function reset() {
    this.scene = new THREE.Scene();
    setup();
}

window.addEventListener('resize', onWindowResize, false);
function onWindowResize(){
    vw = window.innerWidth; vh = window.innerHeight;
    camera.aspect = vw / vh;
    camera.updateProjectionMatrix();
    renderer.setSize( vw, vh );
    reset();
}

function projectToScreen(obj){
    var vector = obj.clone();
    var windowWidth = document.documentElement.clientWidth;
    var widthHalf = (windowWidth/2);
    var heightHalf = (document.documentElement.clientHeight/2);
    vector.project(camera);
    vector.x = ( vector.x * widthHalf ) + widthHalf;
    vector.y = - ( vector.y * heightHalf ) + heightHalf;
    vector.z = 0;
    return vector;
};

function distanceBetweenDimTwo(p1, p2) {
    return sqrt(p(p1.x - p2.x) + p(p1.y - p2.y));
}

function genEdges(distanceThreshold, ctx) {
    for (var i = 0; i < vertices.length; i++) {
        for (var j = i + 1; j < vertices.length; j++) {
            var dist = distanceBetweenDimTwo(vertices[i], vertices[j]);
            if (dist < distanceThreshold) {
                ctx.globalAlpha = map_range(dist, 0, distanceThreshold, 0.5, 0);
                ctx.beginPath();
                ctx.moveTo(vertices[i].x, vertices[i].y);
                ctx.lineTo(vertices[j].x, vertices[j].y);
                ctx.strokeStyle = '#ffffff';
                ctx.stroke();
            }
        }
    }
}

function genRanPtOutsideScreen(array, flag) {
    var perimeter = (canvas.width+ canvas.height) * 2;
    var LEFT = flag != null && flag.indexOf("LEFT") !== -1;
    var RIGHT = flag != null && flag.indexOf("RIGHT") !== -1;

    var ptLoc;
    if (LEFT)
        ptLoc = Math.random() * canvas.height;
    else if (RIGHT)
        ptLoc = Math.random() * canvas.height + canvas.width + canvas.height;
    else
        ptLoc = Math.random() * perimeter;

    if (ptLoc < canvas.height && ptLoc > 0) {
        array.push({
            x: Math.random() * -250,
            y: ptLoc
        });
    } else if (ptLoc < canvas.height + canvas.width && ptLoc > canvas.height) {
        array.push({
            x: ptLoc - canvas.height,
            y: canvas.height + Math.random() * 250
        });
    } else if (ptLoc < canvas.height * 2 + canvas.width && ptLoc > canvas.height + canvas.width) {
        array.push({
            x: canvas.width + Math.random() * 250,
            y: ptLoc - canvas.height - canvas.width
        });
    } else {
        array.push({
            x: ptLoc - canvas.height * 2 - canvas.width,
            y: Math.random() * -250
        });
    }
}

function projectModelVertices(MODEL) {
    vertices = [];
    for (var i = 0; i < MODEL.geometry.vertices.length; i++) {
        vertices.push(MODEL.geometry.vertices[i].clone());
        vertices[i].applyMatrix4(MODEL.matrixWorld);
        vertices[i] = projectToScreen(vertices[i]);
    }
}

////////////////////////////////////////RUNTIME FUNCTIONS////////////////////////////

function initMeshes() {
    var loader = new THREE.JSONLoader();
    var sphereG = new THREE.SphereGeometry(300, 15, 15);
    sphereM = new THREE.Mesh(sphereG);

    var numStars;
    if (canvas.width * canvas.height > 550000)
        numStars = 500;
    else
        numStars = 256;

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

    loader.load('./res/models/test1.json', function(geometry) {
        sBorderM = new THREE.Mesh(geometry);
        sBorderM.scale.x = sBorderM.scale.y = 200;
    });

    /*
    TODO
    var sEarM;
    var sEyeM;
    var sSnoutM;
    var sFadeM;
    */
}

function startTransition(newStage) {
    _goalPointsSatisfied = [];
    _distanceTravelled = [];
    switch(newStage) {
        case STAGE.STARFIELD:
            transitionSpeed = 1;
            _goalPoints = [];
            _distanceTravelled = [];
            for (var i = 0; i < 250; i++) {
                _goalPoints.push({
                    x: starFieldM[i].x,
                    y: starFieldM[i].y
                });
                _distanceTravelled.push(0);
            }

            if (vertices.length < starFieldM.length) {
                vertices.length = 250;
                _goalPoints.length = 250;

                for (var i = 250; i < 500; i++) {
                    genRanPtOutsideScreen(vertices, "LEFT");

                    _goalPoints.push({
                        x: starFieldM[i].x,
                        y: starFieldM[i].y
                    });
                    _distanceTravelled.push(0);
                }
            }
            break;

        case STAGE.STAG:
            transitionSpeed = 0.5;
            sBorderM.updateMatrixWorld();
            _goalPoints = [];

            for (var i = 0; i < starFieldM.length; i++) {
                if (i < sBorderM.geometry.vertices.length) {
                    _goalPoints.push(sBorderM.geometry.vertices[i].clone());
                    _goalPoints[i].applyMatrix4(sBorderM.matrixWorld);
                    _goalPoints[i] = projectToScreen(_goalPoints[i]);
                } else {
                    genRanPtOutsideScreen(_goalPoints, "RIGHT");
                }
                _distanceTravelled.push(0);
            }
            break;
    }
    for (var i = 0; i < _goalPoints.length; i++) {
        _goalPointsSatisfied.push(false);
    }

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

        // We can check if the point is either coming into or out of the screen by its index maybe.
        // then check if it's coming into or out by its corresponding goalPoint

        var SKIP_SPEEDUP = false;
        var SKIP_SLOWDOWN = false;
        switch(newStage) {
            case STAGE.STARFIELD:
                if (i >= 250)
                    SKIP_SPEEDUP = true;
            break;

            case STAGE.STAG:
                if (i >= sBorderM.geometry.vertices.length)
                    SKIP_SLOWDOWN = true;

            break;
        }

        if (progress < markerOne && !SKIP_SPEEDUP) {
            speed = map_range(progress, 0, markerOne, 0.5, 20);
        } else if (/*progress >= markerOne && */progress <= markerTwo) {
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

    if (transitionComplete)
        _stage = newStage;
}

////////////////////////////////////////CREATING OBJECTS/////////////////////////////

var setup = function () {
    renderer.setSize( vw, vh );
    container = document.createElement( 'div' );
    document.body.appendChild( container );
    scene.background = new THREE.Color( 0x1b1b19 );
    canvas = document.getElementById("2d");
    canvas.width = vw;
    canvas.height = vh;
    stats = new Stats();                    //Generate FPS counter
    container.appendChild( stats.dom );
    starFieldM = [];
    starVelocities = [];
    startTime = Date.parse(new Date());
    initMeshes();
}

////////////////////////////////////////RENDERING & ANIMATING/////////////////////////

var render = function () {
    window.requestAnimationFrame( render );
    stats.update();    //Update FPS counter.

    var timeElapsed = Date.now() - startTime;

    //8000, 18000.   1000, 5000
    if (timeElapsed > 1000 && _stage == STAGE.SPHERE) {
        startTransition(STAGE.STARFIELD);
    } else if (timeElapsed > 5000 && _stage == STAGE.STARFIELD) {
        startTransition(STAGE.STAG);
    }

    var canvas = document.getElementById("2d");
    var ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    switch(_stage) {
        case STAGE.TRANSITION:
            switch(_newStage) {
                case STAGE.STARFIELD:
                    transitionSpeed += 0.1;
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
                    transitionSpeed += 0.1;
                    sBorderM.updateMatrixWorld();

                    for (var i = 0; i < sBorderM.geometry.vertices.length; i++) {
                        _goalPoints[i] = sBorderM.geometry.vertices[i].clone();
                        _goalPoints[i].applyMatrix4(sBorderM.matrixWorld);
                        _goalPoints[i] = projectToScreen(_goalPoints[i]);
                    }

                    if (closeEnough > 10)
                        closeEnough -= 1;

                    // GENERATE NEW EDGES.

                    break;
            }
            transitionTo(_newStage);
            genEdges(closeEnough, ctx);
            break;

        case STAGE.SPHERE:
            sphereM.updateMatrixWorld();
            sphereM.rotation.x += 0.001;
            sphereM.rotation.y += 0.001;
            sphereM.rotation.z += 0.001;
            projectModelVertices(sphereM);
            genEdges(closeEnough, ctx);
            break;

        case STAGE.STARFIELD:
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

            genEdges(closeEnough, ctx);
            break;

        case STAGE.STAG:
            if (sBorderM) {
                sBorderM.updateMatrixWorld();
                projectModelVertices(sBorderM);
                
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
            break;
    }

    renderer.render(scene, camera);
};

////////////////////////////////////////RUN/////////////////////////

setup();
render();