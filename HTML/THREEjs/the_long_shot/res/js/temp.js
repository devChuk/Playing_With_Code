/*
Brian Chuk (brianch.uk)
Props for checking out this code
*/

////////////////////////////////////////SETUP////////////////////////////////////////

//Compute some useful values...
var vw = window.innerWidth;
var vh = window.innerHeight;

var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 75, vw/vh, 0.1, 1000 );

var renderer = new THREE.WebGLRenderer();
renderer.setSize( vw, vh );
document.body.appendChild( renderer.domElement );

camera.position.z = 655;
////////////////////////////////////////HELPER FUNCTIONS////////////////////////////////////////

function empty(elem) {
    while (elem.lastChild) elem.removeChild(elem.lastChild);
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


////////////////////////////////////////CREATING OBJECTS////////////////////////////////////////

var setup = function () {

	var material = new THREE.PointsMaterial({
		color: 0xffffcc,
		size: 1,
		vertexColors: THREE.VertexColors
	});

	geometry = new THREE.Geometry();
	movement = [];
	var x, y, z;
	for (var i = 0; i < 1000; i++) {
		x = (Math.random() * vw) - vw/2;
		y = (Math.random() * vh) - vh/2;
	  	z = 0;//(Math.random() * 800) - 400; //-400
	  	geometry.vertices.push(new THREE.Vector3(x, y, z));
		geometry.colors.push(new THREE.Color(250,250,250));

		movement.push({	dX: Math.random() * 2 - 1,
						dY: Math.random() * 2 - 1,
						dZ: Math.random() * 2 - 1});

	}

	var points = new THREE.Points(geometry, material);
	scene.add(points);



}

////////////////////////////////////////RENDERING&&ANIMATING////////////////////////////////////////

var render = function () {
	window.requestAnimationFrame( render );

	geometry.vertices.forEach(function(point, index, array) {
			    // geometry.colors[index] = new THREE.Color(Math.random(), Math.random(), Math.random());
	    point.add(new THREE.Vector3(movement[index].dX, movement[index].dY, movement[index].dZ));
	    
	    // console.log(index);
	});


	geometry.verticesNeedUpdate = true;
	geometry.colorsNeedUpdate = true;

	renderer.render(scene, camera);
};


////////////////////////////////////////RENDERING&&ANIMATING////////////////////////////////////////
setup();
render();