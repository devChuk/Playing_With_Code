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

var renderer = new THREE.WebGLRenderer({antialias: true});
renderer.setSize( vw, vh );
document.body.appendChild( renderer.domElement );

camera.position.z = 655;

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

////////////////////////////////////////CREATING OBJECTS/////////////////////////////

var setup = function () {
    container = document.createElement( 'div' );
    document.body.appendChild( container );

    //Generate FPS counter.
    stats = new Stats();
    container.appendChild( stats.dom );

	var pointMaterial = new THREE.PointsMaterial({
		color: 0xffffcc,
		size: 0,
		vertexColors: THREE.VertexColors
	});

	pointGeometry = new THREE.Geometry();
	movement = [];
	var x, y, z;
	for (var i = 0; i < 100; i++) {
		x = (Math.random() * vw) - vw/2;
		y = (Math.random() * vh) - vh/2;
	  	z = 0;
	  	pointGeometry.vertices.push(new THREE.Vector3(x, y, z));
		pointGeometry.colors.push(new THREE.Color(1,1,1));

		movement.push({	dX: Math.random() * 1 - 0.5,
						dY: Math.random() * 1 - 0.5,
						dZ: Math.random() * 1 - 0.5});
	}

	var points = new THREE.Points(pointGeometry, pointMaterial);
	scene.add(points);

	lineMaterial = new THREE.LineBasicMaterial({
		color: 0xE5E5E5,
		linewidth: 2,
        transparent: true,
        opacity: 0.1
    });
}

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////
var storage = {};

var render = function () {
	window.requestAnimationFrame( render );
    //Update FPS counter.
    stats.update();

    //remove all lines
    for(var i = scene.children.length - 1; i > 0; i--) {        
        scene.children[i].geometry.dispose();
        scene.children[i].material.dispose();
        scene.remove(scene.children[i]);
    }
    for (var member in storage) {
        delete storage[member];
    }
    var indexx = 0;

	pointGeometry.vertices.forEach(function(point, index, array) {
	    if (Math.abs(point.x) >= vw/2) {
			movement[index].dX *= -1;
	    } else if (Math.abs(point.y) >= vh/2) {
	    	movement[index].dY *= -1;
	    } else if (Math.abs(point.z) >= 10) {
	    	movement[index].dZ *= -1;
	    }
	    point.add(new THREE.Vector3(movement[index].dX, movement[index].dY, movement[index].dZ));

        var closeEnough = 200;

        for (var i = index + 1; i < array.length; i++) {
            var dist = sqrt(p(point.x - array[i].x) + p(point.y - array[i].y) + p(point.z - array[i].z));
            if (dist <= closeEnough &&
                scene.children.length <= 600) {
                var lineGeometry = new THREE.Geometry();
                lineGeometry.vertices.push(point);
                lineGeometry.vertices.push(array[i]);
                storage[indexx] = new THREE.Line(lineGeometry, new THREE.LineBasicMaterial(lineMaterial));
                var opacity_input = map_range(dist, 0, closeEnough, 70, 0)/100;
                storage[indexx].material.opacity = opacity_input;
                scene.add(storage[indexx]);
                indexx++;
            }
        }
	});
    pointGeometry.verticesNeedUpdate = true;
	renderer.render(scene, camera);
};

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////
setup();
render();