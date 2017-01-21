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

var renderer = new THREE.WebGLRenderer({antialias: true});
renderer.setSize( vw, vh );
document.body.appendChild( renderer.domElement );

camera.position.z = 655;

closeEnough = 100;
farEnough = 200;

var mesh;

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
    console.log("initMesh start");

    var loader = new THREE.JSONLoader();
    loader.load('./res/js/untitled.json', function(geometry) {
        mesh = new THREE.Mesh(geometry);
        mesh.scale.x = mesh.scale.y = mesh.scale.z = 100;
        scene.add(mesh);
    });

    console.log("initMesh end");
}

////////////////////////////////////////CREATING OBJECTS/////////////////////////////

var setup = function () {
    container = document.createElement( 'div' );
    document.body.appendChild( container );

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


    
    mesh.rotation.x += 0.02;
    mesh.rotation.y += 0.02;
    mesh.rotation.z += 0.02;



    renderer.render(scene, camera);
};

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////
setup();
render();