/*
Brian Chuk (brianch.uk)


Last resort:
http://www.blendswap.com/blends/view/21278
https://www.turbosquid.com/3d-models/deer-blender-3d-model/822899

*/

////////////////////////////////////////SETUP////////////////////////////////////////

// Initiialize & compute some useful values...

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

// runtime values
var STAGE = {
    TRANSITION: 0,
    SPHERE: 1,
    STARFIELD: 2,
    STAG: 3,
};

var _stage = STAGE.SPHERE;
var _newStage;
var _goalPoints;

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

////////////////////////////////////////RUNTIME FUNCTIONS////////////////////////////
function initMeshes() {
    var loader = new THREE.JSONLoader();

    var sphereG = new THREE.SphereGeometry(300, 15, 15);
    sphereM = new THREE.Mesh(sphereG);

    for (var i = 0; i < 500; i++) {
        starFieldM.push({
            x: (Math.random() * canvas.width) - canvas.width/2,
            y: (Math.random() * canvas.width) - canvas.width/2
        });

        starVelocities.push({
            dx: Math.random() * 1 - 0.5,
            dy: Math.random() * 1 - 0.5
        });
    }

    loader.load('./res/models/model2.json', function(geometry) {
    //loader.load('./res/models/stagFiles/ears.json', function(geometry) {
        stagBorderM = new THREE.Mesh(geometry);
        stagBorderM.scale.x = stagBorderM.scale.y = stagBorderM.scale.z = 100;
        //scene.add(stagBorderM);
    });

    
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

function transitionTo(newStage, goalPoints) {
    _stage = STAGE.TRANSITION;
    // if goalPoints not satisfied, then move points

    // if goalPoints are, then update _stage
}

////////////////////////////////////////CREATING OBJECTS/////////////////////////////

var setup = function () {
    renderer.setSize( vw, vh );
    container = document.createElement( 'div' );
    document.body.appendChild( container );
    scene.background = new THREE.Color( 0x1b1b19 );

    var canvas = document.getElementById("2d");
    canvas.width = vw;
    canvas.height = vh;

    //Generate FPS counter.
    stats = new Stats();
    container.appendChild( stats.dom );

    initMeshes();
}

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////

var render = function () {
    window.requestAnimationFrame( render );
    //Update FPS counter.
    stats.update();

    var canvas = document.getElementById("2d");
    var ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    switch(_stage) {
        case STAGE.TRANSITION:
                transitionTo(newStage, newPoints);
            break;
        case STAGE.SPHERE:
            sphereM.updateMatrixWorld();
            sphereM.rotation.x += 0.004;
            sphereM.rotation.y += 0.005;
            sphereM.rotation.z += 0.008;

            vertices = [];
            for (var i = 0; i < sphereM.geometry.vertices.length; i++) {
                vertices.push(sphereM.geometry.vertices[i].clone());
                vertices[i].applyMatrix4(sphereM.matrixWorld);
                vertices[i] = projectToScreen(vertices[i]);
            }

            for (var i = 0; i < vertices.length; i++) {
                for (var j = i + 1; j < vertices.length; j++) {
                        var dist = vertices[i].distanceTo(vertices[j]);
                        if (dist < closeEnough) {
                            ctx.globalAlpha = map_range(dist, 0, closeEnough, 0.5, 0);
                            ctx.beginPath();
                            ctx.moveTo(vertices[i].x, vertices[i].y);
                            ctx.lineTo(vertices[j].x, vertices[j].y);
                            ctx.strokeStyle = '#ffffff';
                            ctx.stroke();
                        }
                }
            }
            break;
        case STAGE.STARFIELD:
            //for (var i = 0; i < starFieldM.length; )

            // loop through all starField vertices
                // move each vertice based on movement[]
            // double for loop them and create lines

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

                for (var i = 0; i < vertices.length; i++) {
                    for (var j = i + 1; j < vertices.length; j++) {
                            var dist = vertices[i].distanceTo(vertices[j]);
                            if (dist < closeEnough) {
                                ctx.globalAlpha = map_range(dist, 0, closeEnough, 0.5, 0);
                                ctx.beginPath();
                                ctx.moveTo(vertices[i].x, vertices[i].y);
                                ctx.lineTo(vertices[j].x, vertices[j].y);
                                ctx.strokeStyle = '#ffffff';
                                ctx.stroke();
                            }
                    }
                }
            }
            break;
    }

    renderer.render(scene, camera);
};

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////
setup();
render();