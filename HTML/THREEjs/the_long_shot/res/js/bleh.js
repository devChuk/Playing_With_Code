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

////////////////////////////////////////CREATING OBJECTS////////////////////////////////////////

var setup = function () {
    container = document.createElement( 'div' );
    document.body.appendChild( container );
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
	for (var i = 0; i < 200; i++) {
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
		color: 0x303030,
		linewidth: 2
    });

    // lineGeometry = new THREE.Geometry();

    pointGeometry.vertices.forEach(function(point, index, array) {
        for (var i = index + 1; i < array.length; i++) {
            
            if (sqrt(p(point.x - array[i].x) + p(point.y - array[i].y) + p(point.z - array[i].z)) <= 150) {
                var lineGeometry = new THREE.Geometry();
                lineGeometry.vertices.push(point);
                lineGeometry.vertices.push(array[i]);
                scene.add(new THREE.Line(lineGeometry, lineMaterial));
            }


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
    stats.update();

    //remove everything
    for(var i = scene.children.length - 1; i > 0; i--) {
        // scene.children[i].deallocate();
        
        scene.children[i].geometry.dispose();
        scene.children[i].material.dispose();
        scene.remove(scene.children[i]);
    }
    for (var member in storage) {
        // storage[member].deallocate();
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


        for (var i = index + 1; i < array.length; i++) {
            var dist = sqrt(p(point.x - array[i].x) + p(point.y - array[i].y) + p(point.z - array[i].z));
            if (dist <= 130 &&
                scene.children.length <= 600) {
                // lineGeometry.vertices.push(newTHREE)   (point.x - array[i].x)
                var lineGeometry = new THREE.Geometry();
                lineGeometry.vertices.push(point);
                lineGeometry.vertices.push(array[i]);
                storage[indexx] = new THREE.Line(lineGeometry, new THREE.LineBasicMaterial(lineMaterial));
                var hsl_string = "hsl(0, 0%, " + map_range(dist, 0, 130, 100, 0) + "%)";
                storage[indexx].material.color = new THREE.Color(hsl_string);
                scene.add(storage[indexx]);
                indexx++;
            }

        }
	});
    pointGeometry.verticesNeedUpdate = true;
	renderer.render(scene, camera);
};

////////////////////////////////////////RENDERING&&ANIMATING////////////////////////////////////////
setup();
render();