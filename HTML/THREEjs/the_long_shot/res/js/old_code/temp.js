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

////////////////////////////////////////HELPER FUNCTIONS////////////////////////////////////////

function p(num) {return Math.pow(num, 2);}
function sqrt(num) {return Math.sqrt(num);}

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

	var pointMaterial = new THREE.PointsMaterial({
		color: 0xffffcc,
		size: 1,
		vertexColors: THREE.VertexColors
	});

	pointGeometry = new THREE.Geometry();
	movement = [];
	var x, y, z;
	for (var i = 0; i < 300; i++) {
		x = (Math.random() * vw) - vw/2;
		y = (Math.random() * vh) - vh/2;
	  	z = 0;
	  	pointGeometry.vertices.push(new THREE.Vector3(x, y, z));
		pointGeometry.colors.push(new THREE.Color(250,250,250));

		movement.push({	dX: Math.random() * 1 - 0.5,
						dY: Math.random() * 1 - 0.5,
						dZ: Math.random() * 1 - 0.5});


	}

	var points = new THREE.Points(pointGeometry, pointMaterial);
	scene.add(points);



	lineMaterial = new THREE.LineBasicMaterial({
		color: 0x303030,
		linewidth: 1
    });
    /*
        2B2B2B
    */

    lineGeometry = new THREE.Geometry();

    pointGeometry.vertices.forEach(function(point, index, array) {
        for (var i = index + 1; i < array.length; i++) {
            var lineGeometry = new THREE.Geometry();
            lineGeometry.vertices.push(point);
            lineGeometry.vertices.push(array[i]);
            scene.add(new THREE.Line(lineGeometry, lineMaterial));
        }
    });
    // lineGeometry.vertices.push(new THREE.Vector3(-100, 0, 0));
    // lineGeometry.vertices.push(new THREE.Vector3(0, 100, 0));
    // lineGeometry.vertices.push(new THREE.Vector3(100, 0, 0));
    // var line = new THREE.Line(lineGeometry, lineMaterial);
    // scene.add(line);


}

////////////////////////////////////////RENDERING&&ANIMATING////////////////////////////////////////
var storage = {};


var render = function () {
	window.requestAnimationFrame( render );

    //remove everything
    // for(var i = scene.children.length - 1; i > 0; i--) {
    //     scene.remove(scene.children[i]);
    // }
    // for (var member in storage)
    //     delete storage[member];
    // var indexx = 0;

	pointGeometry.vertices.forEach(function(point, index, array) {
	    if (Math.abs(point.x) >= vw/2) {
			movement[index].dX *= -1;
	    } else if (Math.abs(point.y) >= vh/2) {
	    	movement[index].dY *= -1;
	    } else if (Math.abs(point.z) >= 100) {
	    	movement[index].dZ *= -1;
	    }
	    point.add(new THREE.Vector3(movement[index].dX, movement[index].dY, movement[index].dZ));


        // for (var i = index + 1; i < array.length; i++) {
        //     if (sqrt(p(point.x - array[i].x) + p(point.y - array[i].y) + p(point.z - array[i].z)) <= 150) {
        //         // lineGeometry.vertices.push(newTHREE)   (point.x - array[i].x)
        //         var lineGeometry = new THREE.Geometry();
        //         lineGeometry.vertices.push(point);
        //         lineGeometry.vertices.push(array[i]);
        //         storage[indexx] = new THREE.Line(lineGeometry, lineMaterial);
        //         scene.add(storage[indexx]);
        //         indexx++;
        //     }

        // }
	});
    pointGeometry.verticesNeedUpdate = true;
	renderer.render(scene, camera);
};

////////////////////////////////////////RENDERING&&ANIMATING////////////////////////////////////////
setup();

    // pointGeometry.vertices.forEach(function(point, index, array) {
    //     if (Math.abs(point.x) >= vw/2) {
    //         movement[index].dX *= -1;
    //     } else if (Math.abs(point.y) >= vh/2) {
    //         movement[index].dY *= -1;
    //     } else if (Math.abs(point.z) >= 100) {
    //         movement[index].dZ *= -1;
    //     }
    //     point.add(new THREE.Vector3(movement[index].dX, movement[index].dY, movement[index].dZ));


    //     for (var i = index + 1; i < array.length; i++) {
    //         if (sqrt(p(point.x - array[i].x) + p(point.y - array[i].y) + p(point.z - array[i].z)) <= 150) {
    //             // lineGeometry.vertices.push(newTHREE)   (point.x - array[i].x)
    //             var lineGeometry = new THREE.Geometry();
    //             lineGeometry.vertices.push(point);
    //             lineGeometry.vertices.push(array[i]);
    //             var line = new THREE.Line(lineGeometry, lineMaterial);
    //             scene.add(line);
    //         }

    //     }
    // });

render();