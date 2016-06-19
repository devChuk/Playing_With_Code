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

camera.position.z = 5;

////////////////////////////////////////CREATING OBJECTS////////////////////////////////////////


// var geometry = new THREE.BoxGeometry( 1, 1, 1 );
// var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
// var cube = new THREE.Mesh( geometry, material );
// scene.add( cube );

var material = new THREE.PointsMaterial({
	color: 0xffffcc,
	size: 1,
	vertexColors: THREE.VertexColors
});

var geometry = new THREE.Geometry();
var x, y, z;
for (var i = 0; i < 1000; i++) {
	x = (Math.random() * 800) - 400;
	y = (Math.random() * 800) - 400;
  	z = (Math.random() * 800) - 400;
  	geometry.vertices.push(new THREE.Vector3(x, y, z));
	geometry.colors.push(new THREE.Color(Math.random(), Math.random(), Math.random()));
}

var points = new THREE.Points(geometry, material);
scene.add(points);


////////////////////////////////////////RENDERING&&ANIMATING////////////////////////////////////////

var render = function () {
	window.requestAnimationFrame( render );

	geometry.vertices.forEach(function(point, index, array) {
		var dX, dY, dZ;
	    dX = 4;//Math.random() * 2 - 1;
	    // dY = Math.random() * 2 - 1;
	    // dZ = Math.random() * 2 - 1;

	    geometry.colors[index] = new THREE.Color(Math.random(), Math.random(), Math.random());
	    point.add(new THREE.Vector3(dX, dY, dZ));
	    
	    // console.log(index);
	});


	geometry.verticesNeedUpdate = true;
	geometry.colorsNeedUpdate = true;

	renderer.render(scene, camera);
};

render();

/*
http://stackoverflow.com/questions/31289577/three-js-position-particles-evenly-on-objects-faces-rather-than-verticies
http://stackoverflow.com/questions/28285573/making-a-3d-earth-made-up-of-particles-with-three-js
https://github.com/mrdoob/three.js/issues/1591
http://stemkoski.blogspot.com/2013/06/creating-particle-effects-engine-in.html
*/


/* Other stuff
http://learningthreejs.com/blog/2011/09/16/performance-caching-material/
http://stackoverflow.com/questions/31289577/three-js-position-particles-evenly-on-objects-faces-rather-than-verticies
http://stackoverflow.com/questions/28285573/making-a-3d-earth-made-up-of-particles-with-three-js
http://threejs.org/docs/#Reference/Materials/PointsMaterial
http://threejs.org/docs/#Reference/Objects/Points
http://stackoverflow.com/questions/16766524/how-to-produce-particle-system-in-three-js
http://stemkoski.blogspot.com/2013/06/creating-particle-effects-engine-in.html
https://www.google.com/search?q=how+to+use+gpu+threejs&oq=how+to+use+gpu+threejs&aqs=chrome..69i57.4607j0j4&sourceid=chrome&ie=UTF-8
http://www.html5rocks.com/en/tutorials/webgl/million_letters/
https://aerotwist.com/tutorials/getting-started-with-three-js/
http://stackoverflow.com/questions/29673879/gpu-picking-in-three-js
http://stackoverflow.com/questions/21851349/freeing-memory-in-three-js
http://blog.stevensanderson.com/2014/06/11/write-massively-parallel-gpu-code-for-the-browser-with-webgl-ndc-2014/
*/


// TODO
// Make a particle cloud 												CHECK AY
// ANIMATE PARTICLES IN OPENING MOTION									
// SEE IF I CAN MOVE THEM INTO A 3D MODELLED cube
// Consider somehow animating this cube for science.
// If so, let's make a dank deer
// ???







//need to consider performance issues and look into animations that change depending on networks & screen size.
//also do animations stop running when the tab is off?