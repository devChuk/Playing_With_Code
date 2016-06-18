/*
Brian Chuk (brianch.uk)
Props for checking out this code
*/

////////////////////////////////////////SETUP////////////////////////////////////////

var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 75, window.innerWidth/window.innerHeight, 0.1, 1000 );

var renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

window.addEventListener( 'resize', onWindowResize, false );

function onWindowResize(){

    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();

    renderer.setSize( window.innerWidth, window.innerHeight );

}

////////////////////////////////////////CREATING OBJECTS////////////////////////////////////////


var geometry = new THREE.BoxGeometry( 1, 1, 1 );
var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
var cube = new THREE.Mesh( geometry, material );
scene.add( cube );



camera.position.z = 5;


var render = function () {
	requestAnimationFrame( render );

	cube.rotation.x += 0.1;
	cube.rotation.y += 0.1;

	renderer.render(scene, camera);
};

render();

/*
http://stackoverflow.com/questions/31289577/three-js-position-particles-evenly-on-objects-faces-rather-than-verticies
http://stackoverflow.com/questions/28285573/making-a-3d-earth-made-up-of-particles-with-three-js
https://github.com/mrdoob/three.js/issues/1591
*/


// TODO
// Make a particle cloud
// ANIMATE PARTICLES IN OPENING MOTION
// SEE IF I CAN MOVE THEM INTO A 3D MODELLED cube
// Consider somehow animating this cube for science.
// If so, let's make a dank deer
// ???