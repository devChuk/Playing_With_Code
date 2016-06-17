/*
Title:			BrianCh.uk Home Screen Javascript ThreeJS Animation v1
Author:			Brian Chuk (brianch.uk)
Copyright: 		2015, Brian Chuk - All rights reserved (you have permission to use it, just tell me :D)

I would use some of my other animations for the background, but I've found that it was too distracting haha.
Test users would just stare at the animation & not realize that they could scroll down haha

*/

var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 75, window.innerWidth/window.innerHeight, 0.1, 1000 );

var renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

// var geometry = new THREE.BoxGeometry( 1, 1, 1 );
// var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
// var cube = new THREE.Mesh( geometry, material );
// scene.add( cube );



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