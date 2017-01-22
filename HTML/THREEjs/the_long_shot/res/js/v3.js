/*
Brian Chuk (brianch.uk)


Last resort:
http://www.blendswap.com/blends/view/21278
https://www.turbosquid.com/3d-models/deer-blender-3d-model/822899

*/

////////////////////////////////////////SETUP////////////////////////////////////////

//Compute some useful values...
var vw = window.innerWidth;
var vh = window.innerHeight;

var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 75, vw/vh, 0.1, 1000 );

var modelCanvas = document.getElementById("3d");
var renderer = new THREE.WebGLRenderer({antialias: true,
                                        canvas: modelCanvas});

camera.position.z = 655;
var closeEnough = 130;
// var farEnough = 130;
opacityLvl = 0.05;
/* 130 240 */

var model;

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

function initMesh() {
    var loader = new THREE.JSONLoader();
    loader.load('./res/models/model2.json', function(geometry) {
        model = new THREE.Mesh(geometry);
        model.scale.x = model.scale.y = model.scale.z = 100;
        //scene.add(model);
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

    initMesh();
}

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////

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

        vertices = [];
        for (var i = 0; i < model.geometry.vertices.length; i++) {
            vertices.push(model.geometry.vertices[i].clone());
            vertices[i].applyMatrix4(model.matrixWorld);
            vertices[i] = projectToScreen(vertices[i]);
            //ctx.fillRect(vertices[i].x, vertices[i].y, 10, 10);
        }

        for (var i = 0; i < vertices.length; i++) {
            for (var j = i + 1; j < vertices.length; j++) {
                    var dist = vertices[i].distanceTo(vertices[j]);
                    if (dist < closeEnough) {
                        // if (dist < (farEnough + closeEnough) / 2)
                        //     ctx.globalAlpha = map_range(dist, farEnough, closeEnough, 0.3, 0.05)/100;
                        // else
                        //     ctx.globalAlpha = map_range(dist, closeEnough, farEnough, 0.3, 0.05)/100;

                        ctx.globalAlpha = map_range(dist, 0, closeEnough, 0.5, 0);
                        // ctx.globalAlpha=opacityLvl;
                        ctx.beginPath();
                        ctx.moveTo(vertices[i].x, vertices[i].y);
                        ctx.lineTo(vertices[j].x, vertices[j].y);
                        ctx.strokeStyle = '#ffffff';
                        ctx.stroke();
                    }
            }
        }


    }

    renderer.render(scene, camera);
};

////////////////////////////////////////RENDERING&&ANIMATING/////////////////////////
setup();
render();