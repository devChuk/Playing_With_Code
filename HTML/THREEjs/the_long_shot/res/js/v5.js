/*
Brian Chuk (brianch.uk)


Last resort:
http://www.blendswap.com/blends/view/21278
https://www.turbosquid.com/3d-models/deer-blender-3d-model/822899

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
opacityLvl = 0.05;
/* 130 240 */

// HTML Canvas variables
var canvas;
var starCloseEnough;

// runtime values
var startTime;
var timeElapsed;
var STAGE = {
    TRANSITION: 0,
    SPHERE: 1,
    STARFIELD: 2,
    STAG: 3,
};

var _stage = STAGE.SPHERE;
var vertices;
var _goalMovements;
var _goalPoints;
var _goalPointsSatisfied;
var _newStage;
var transitionSpeed = 0.5;

// sphere model
var sphereM;

// starfield model
var starFieldM = [];
var starVelocities = [];

// stag model
var stagBorderM;
var stagEarM;
var stagEyeM;
var stagSnoutM;
var stagFadeM;

////////////////////////////////////////HELPER FUNCTIONS/////////////////////////////

function p(num) {return Math.pow(num, 2);}
function sqrt(num) {return Math.sqrt(num);}
function map_range(value, low1, high1, low2, high2) {
    return (low2 + (high2 - low2) * (value - low1) / (high1 - low1));
}

function reset() {
    this.scene = new THREE.Scene();
    setup();
}

window.addEventListener( 'resize', onWindowResize, false );
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

function distanceBetween(p1, p2) {
    return sqrt(p(p1.x - p2.x) + p(p1.y - p2.y));
}

function genEdges(distanceThreshold, ctx) {
    for (var i = 0; i < vertices.length; i++) {
        for (var j = i + 1; j < vertices.length; j++) {
            var dist = distanceBetween(vertices[i], vertices[j]);
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

function genRanPtOutsideScreen(array) {
    var perimeter = (canvas.width+ canvas.height) * 2;
    var ptLoc = Math.random() * perimeter;
    if (ptLoc < canvas.height && ptLoc > 0) {
        array.push({
            x: Math.random() * -500,
            y: ptLoc
        });
    } else if (ptLoc < canvas.height + canvas.width && ptLoc > canvas.height) {
        array.push({
            x: ptLoc - canvas.height,
            y: canvas.height + Math.random() * 500
        });
    } else if (ptLoc < canvas.height * 2 + canvas.width && ptLoc > canvas.height + canvas.width) {
        array.push({
            x: canvas.width + Math.random() * 500,
            y: ptLoc - canvas.height - canvas.width
        });
    } else {
        array.push({
            x: ptLoc - canvas.height * 2 - canvas.width,
            y: Math.random() * -500
        });
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

    loader.load('./res/models/model2.json', function(geometry) {
        stagBorderM = new THREE.Mesh(geometry);
        stagBorderM.scale.x = stagBorderM.scale.y = stagBorderM.scale.z = 100;
    });

    
}

function startTransition(newStage) {
    _goalPointsSatisfied = [];
    switch(newStage) {
        case STAGE.STARFIELD:
            transitionSpeed = 1;
            _goalPoints = [];
            for (var i = 0; i < 250; i++) {
                _goalPoints.push({
                    x: starFieldM[i].x,
                    y: starFieldM[i].y
                });
            }

            if (vertices.length < starFieldM.length) {
                vertices.length = 250;
                _goalPoints.length = 250;

                for (var i = 250; i < 500; i++) {
                    genRanPtOutsideScreen(vertices);

                    _goalPoints.push({
                        x: starFieldM[i].x,
                        y: starFieldM[i].y
                    });
                }
            }
            break;
        case STAGE.STAG:
            transitionSpeed = 0.5;
            stagBorderM.updateMatrixWorld();
            _goalPoints = [];

            for (var i = 0; i < starFieldM.length; i++) {
                if (i < stagBorderM.geometry.vertices.length) {
                    _goalPoints.push(stagBorderM.geometry.vertices[i].clone());
                    _goalPoints[i].applyMatrix4(stagBorderM.matrixWorld);
                    _goalPoints[i] = projectToScreen(_goalPoints[i]);
                } else {
                    genRanPtOutsideScreen(_goalPoints);
                }
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
    for (var i = 0; i < vertices.length; i++) {
        var diffX = _goalPoints[i].x - vertices[i].x;
        var diffY = _goalPoints[i].y - vertices[i].y;
        var magnitude = sqrt(p(diffX) + p(diffY));

        _goalMovements.push({dx: diffX/magnitude * transitionSpeed,
                             dy: diffY/magnitude * transitionSpeed});
    }

    for (var i = 0; i < vertices.length; i++) {
        if (_goalPointsSatisfied[i] == false && (vertices[i].x != _goalPoints[i].x && vertices[i].y != _goalPoints[i].y)) {
            transitionComplete = false;

            if (sqrt(p(_goalPoints[i].x - vertices[i].x) + p(_goalPoints[i].y - vertices[i].y)) > transitionSpeed) {
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

    //Generate FPS counter.
    stats = new Stats();
    container.appendChild( stats.dom );

    starFieldM = [];
    starVelocities = [];

    startTime = Date.parse(new Date());
    initMeshes();
}

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////

var render = function () {
    window.requestAnimationFrame( render );
    //Update FPS counter.
    stats.update();

    var timeElapsed = Date.now() - startTime;

    if (timeElapsed > 8000 && _stage == STAGE.SPHERE) {
        startTransition(STAGE.STARFIELD);
    } else if (timeElapsed > 16000 && _stage == STAGE.STARFIELD) {
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
                    stagBorderM.updateMatrixWorld();
                    stagBorderM.rotation.x += 0.01;
                    stagBorderM.rotation.y += 0.01;

                    for (var i = 0; i < stagBorderM.geometry.vertices.length; i++) {
                        _goalPoints[i] = stagBorderM.geometry.vertices[i].clone();
                        _goalPoints[i].applyMatrix4(stagBorderM.matrixWorld);
                        _goalPoints[i] = projectToScreen(_goalPoints[i]);
                    }
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

            vertices = [];
            for (var i = 0; i < sphereM.geometry.vertices.length; i++) {
                vertices.push(sphereM.geometry.vertices[i].clone());
                vertices[i].applyMatrix4(sphereM.matrixWorld);
                vertices[i] = projectToScreen(vertices[i]);
            }

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
            if (stagBorderM) {
                stagBorderM.updateMatrixWorld();
                stagBorderM.rotation.x += 0.01;
                stagBorderM.rotation.y += 0.01;

                vertices = [];
                for (var i = 0; i < stagBorderM.geometry.vertices.length; i++) {
                    vertices.push(stagBorderM.geometry.vertices[i].clone());
                    vertices[i].applyMatrix4(stagBorderM.matrixWorld);
                    vertices[i] = projectToScreen(vertices[i]);
                }

                genEdges(closeEnough, ctx);
            }
            break;
    }

    renderer.render(scene, camera);
};

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////
setup();
render();