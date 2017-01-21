/*
Brian Chuk (brianch.uk)


file:///home/brian_chuk/Desktop/Playing_With_Code/HTML/THREEjs/the_long_shot/index.html
*/

////////////////////////////////////////SETUP////////////////////////////////////////

//Compute some useful values...
var vw = window.innerWidth;
var vh = window.innerHeight;

var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 75, vw/vh, 0.1, 1000 );

var threedcanvas = document.getElementById("3d");
var renderer = new THREE.WebGLRenderer({antialias: true,
                                        canvas: threedcanvas});
renderer.setSize( vw, vh );
scene.background = new THREE.Color( 0xffe0f4 );
//document.body.appendChild( renderer.domElement );

camera.position.z = 655;

closeEnough = 100;
farEnough = 200;

var model;

////////////////////////////////////////HELPER FUNCTIONS/////////////////////////////

function p(num) {return Math.pow(num, 2);}
function sqrt(num) {return Math.sqrt(num);}
function map_range(value, low1, high1, low2, high2) {
    return Math.round(low2 + (high2 - low2) * (value - low1) / (high1 - low1));
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

function initMesh() {
    var loader = new THREE.JSONLoader();
    loader.load('./res/js/model.json', function(geometry) {
        model = new THREE.Mesh(geometry);
        model.scale.x = model.scale.y = model.scale.z = 100;
        scene.add(model);
    });
}

function screenXY(obj){

    var vector = obj.clone();
    var windowWidth = document.documentElement.clientWidth;
    // var minWidth = 1280; // may need to edit this lol

    // if(windowWidth < minWidth) {
    // windowWidth = minWidth;
    // }

    var widthHalf = (windowWidth/2);
    var heightHalf = (document.documentElement.clientHeight/2);

    vector.project(camera);

    vector.x = ( vector.x * widthHalf ) + widthHalf;
    vector.y = - ( vector.y * heightHalf ) + heightHalf;
    vector.z = 0;

    return vector;
};

////////////////////////////////////////CREATING OBJECTS/////////////////////////////

var setup = function () {
    container = document.createElement( 'div' );
    document.body.appendChild( container );
    scene.background = new THREE.Color( 0xffe0f4 );

    var canvas = document.getElementById("2d");
    canvas.width = vw;
    canvas.height = vh;

    //Generate FPS counter.
    stats = new Stats();
    container.appendChild( stats.dom );

    initMesh();
}

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////
var storage = {};

var render = function () {
    window.requestAnimationFrame( render );
    //Update FPS counter.
    stats.update();

    var canvas = document.getElementById("2d");
    var ctx = canvas.getContext("2d");
    ctx.fillStyle = "green";
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    if (model) {
        model.updateMatrixWorld();

        model.rotation.x += 0.02;
        model.rotation.y += 0.02;
        // model.rotation.z += 0.02;

        vertices = [];
        for (var i = 0; i < model.geometry.vertices.length; i++) {
            vertices.push(model.geometry.vertices[i].clone());
            vertices[i].applyMatrix4(model.matrixWorld);
            vertices[i] = screenXY(vertices[i]);
            ctx.fillRect(vertices[i].x, vertices[i].y, 10, 10);
        }


    }

    renderer.render(scene, camera);
};

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////
setup();
render();