/*
Brian Chuk (brianch.uk)
Message me on my website and say hello! :)
Or tweet or email at me
*/

////////////////////////////////////////SETUP////////////////////////////////////////

// ThreeJS variables
var vw = window.innerWidth;
var vh = window.innerHeight;
var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 75, vw/vh, 0.1, 1000 );
var renderer = new THREE.WebGLRenderer({antialias: true});
var renderID;
camera.position.z = 655;

// HTML Canvas variables
var canvas;

// Runtime values
var startTime;
var STAGE = {
    TRANSITION: 0,
    SPHERE: 1,
    STARFIELD: 2,
    STAG: 3
};
var closeEnough = 130;


// Runtime generated models
var sphereM;
var starFieldM = [];            // contains vertices of a randomized starfield
var starVelocities = [];        // contains velocities of said starfield

// Blender 3D models
var sBorderM;                   // (the s stands for stag. Which means yung male deer)
var sEyeM;
var sEarLM;
var sEarRM;
var sSnoutM;

var sBorderV = [];
var sEyeV = [];
var sEarLV = [];
var sEarRV = [];
var sSnoutV = [];

// Transition values
var _stage = STAGE.SPHERE;      // keeps track of current stage
var vertices;                   // contains all the vertices to render
var _distanceTravelled;         // records distance travelled for each vertex during transitions
var _goalPoints;                // contains the destinations of each vertex after transitions
var _goalMovements;             // contains directions used for transitions for each vertex
var _goalPointsSatisfied;       // contains status of transition completion for each vertex
var _speeds;                    // contains the speeds of each vertex during transitions. Ideally for Material Design
var _newStage;                  // contains the goal stage
var _sFadeIn = 0;               // fades in stag connections
var _sGoalDistance = [];        // stores the goal distances of the stag border vertices

// Stag rendering values
var earCloseEnough = 35;
var finalcloseEnough = 100;
var numInnerStagPts = 250;
_stage = STAGE.STARFIELD;
var proxThres = [];

var baseTriangles = {
    v: [],                      // stores vertices of triangles
    i: [],                      // stores the actual triangles
    aR: []                      // stores the ratios of triangle areas to entire area
};
var leftEarTriangles = {
    v: [],
    i: [],
    aR: []
};
var rightEarTriangles = {
    v: [],
    i: [],
    aR: []
};

var innerBorderPts = [];
var leftEarPts = [];
var rightEarPts = [];
var mainStagV = [];

// DEBUGGING
var triangleColors = [];


////////////////////////////////////////HELPER FUNCTIONS/////////////////////////////

function p(num) {return Math.pow(num, 2);}
function sqrt(num) {return Math.sqrt(num);}
function map_range(value, low1, high1, low2, high2) {return (low2 + (high2 - low2) * (value - low1) / (high1 - low1));}
function reset() {this.scene = new THREE.Scene(); setup();}
function distanceBetweenDimTwo(p1, p2) {return sqrt(p(p1.x - p2.x) + p(p1.y - p2.y));}
function scalarPtMultiply(k, pt) {return {x: k*pt.x,y: k*pt.y};}
function pointAdd(a, b) {return {x: a.x + b.x,y: a.y + b.y};}

function areaOfTriangle(data, tIndexes) {
    // shoelace theorem
    var a = tIndexes[0];
    var b = tIndexes[1];
    var c = tIndexes[2];

    return Math.abs(
            (data[a].x - data[c].x) * (data[b].y - data[a].y) -
            (data[a].x - data[b].x) * (data[c].y - data[a].y)) / 2;
}

function onSeg(a, b, c) {
    // checks if b lies on ac
    return distanceBetweenDimTwo(a,b) + distanceBetweenDimTwo(b,c) == distanceBetweenDimTwo(a,c);
    // -epsilon < (distance(a, c) + distance(c, b) - distance(a, b)) < epsilon
}

function orientation(p, q, r) {
    var val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) {
        return 0;  // colinear
    }
    return (val > 0) ? 1: 2; // clock or counterclock wise
}

function doIntersect(p1, q1, p2, q2) { //border first
    // checks for p1-q1 vs p2-q2

    // Find the four orientations needed for general and special cases
    var o1 = orientation(p1, q1, p2);
    var o2 = orientation(p1, q1, q2);
    var o3 = orientation(p2, q2, p1);
    var o4 = orientation(p2, q2, q1);
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSeg(p1, p2, q1)) return false;
 
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSeg(p1, q2, q1)) return false;
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSeg(p2, p1, q2)) return false;
 
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSeg(p2, q1, q2)) return false;
 
    // General case
    if (o1 != o2 && o3 != o4) {
        
        return true;
    }
 
    
 
    return false; // Doesn't fall in any of the above cases
}

function lineSegExitsPolygn(a, b, polygon) {
    // loop thru all line segments of the polygon
    for (var i = 0; i < polygon.length - 1; i++) {
        var c = polygon[i];
        var d = polygon[i+1];

        if (doIntersect(c, d, a, b) == true) {
            return true;
        }
    }
        // check if line segments intersect
        
        // OPTION A
        // if there are more than 1 intersection, then it intersects

        // if there is an intersection point, check if it's actually one of the endpoints
            // if it is, it doesn't exit
            // if it isn't, it exits
    return false;
}



window.addEventListener('resize', onWindowResize, false);
function onWindowResize(){
    vw = window.innerWidth; vh = window.innerHeight;
    camera.aspect = vw / vh;
    camera.updateProjectionMatrix();
    renderer.setSize( vw, vh );
    reset();
}

function projectToScreen(threeDimPoint){
    var point = threeDimPoint.clone();
    var winWidthHalf = (document.documentElement.clientWidth/2);
    var winHeightHalf = (document.documentElement.clientHeight/2);
    point.project(camera);
    point.x = ( point.x * winWidthHalf ) + winWidthHalf;
    point.y = - ( point.y * winHeightHalf ) + winHeightHalf;
    point.z = 0;
    return point;
};

function projectModelVertices(mesh) {
    var startIndex = vertices.length;

    for (var i = 0; i < mesh.geometry.vertices.length; i++) {
        vertices.push(mesh.geometry.vertices[i].clone());
        vertices[i + startIndex].applyMatrix4(mesh.matrixWorld);
        vertices[i + startIndex] = projectToScreen(vertices[i + startIndex]);
    }
}

function genProjectedVertices(model, projectedVertices) {
    model.updateMatrixWorld();

    for (var i = 0; i < model.geometry.vertices.length; i++) {
        var b = model.geometry.vertices[i].clone();
        b.applyMatrix4(model.matrixWorld);
        b = projectToScreen(b);
        delete b.z;
        projectedVertices.push(b);
    }
}

function genRandPtOutsideScreen(array, flag) {
    var perimeter = (canvas.width+ canvas.height) * 2;
    var LEFT = flag != null && flag.indexOf("LEFT") !== -1;
    var RIGHT = flag != null && flag.indexOf("RIGHT") !== -1;
    var ptLoc;
    var maxDistFromScreenEdge = 250;

    if (LEFT) {
        ptLoc = Math.random() * canvas.height;
    } else if (RIGHT) {
        ptLoc = Math.random() * canvas.height + canvas.width + canvas.height;
    } else {
        ptLoc = Math.random() * perimeter;
    }

    if (LEFT || (0 < ptLoc && ptLoc < canvas.height)) {
        array.push({
            x: Math.random() * -maxDistFromScreenEdge,
            y: ptLoc
        });
    } else if (canvas.height < ptLoc && ptLoc < canvas.height + canvas.width) {
        array.push({
            x: ptLoc - canvas.height,
            y: canvas.height + Math.random() * maxDistFromScreenEdge
        });
    } else if (RIGHT || (ptLoc < canvas.height * 2 + canvas.width && ptLoc > canvas.height + canvas.width)) {
        array.push({
            x: canvas.width + Math.random() * maxDistFromScreenEdge,
            y: ptLoc - canvas.height - canvas.width
        });
    } else {
        array.push({
            x: ptLoc - canvas.height * 2 - canvas.width,
            y: Math.random() * -maxDistFromScreenEdge
        });
    }
}

function genRandPtFromTriangles(array, triObj) {
    var x = Math.random()
    var index = -1;
    while (x >= 0 && index <= triObj.aR.length - 1) {
        // selects a random triangle from the set
        x -= triObj.aR[++index];
    }
    if (triObj.i[index] == undefined) {
        console.log(index);
        return;
    }

    var a = triObj.v[triObj.i[index][0]];
    var b = triObj.v[triObj.i[index][1]];
    var c = triObj.v[triObj.i[index][2]];
    // gen rand pt in triangle

    // from https://math.stackexchange.com/questions/18686/uniform-random-point-in-triangle
    var r1 = Math.random(), r2 = Math.random();
    a = pointAdd(scalarPtMultiply(1 - sqrt(r1), a),
                 scalarPtMultiply(sqrt(r1) * (1 - r2), b));
    array.push(pointAdd(scalarPtMultiply(sqrt(r1) * r2, c),
                        a));
}

function triangulate(arrayOfVertices, holeVertices) {
    var flattenedArray = [];
    var holeIndexes = [];
    var result = [];

    for (var i = 0; i < arrayOfVertices.length; i++) {
        flattenedArray.push(arrayOfVertices[i].x);
        flattenedArray.push(arrayOfVertices[i].y);
    }
    if (holeVertices) {
        for (var i = 0; i < holeVertices.length; i++) {
            holeIndexes.push(flattenedArray.length / 2);

            for (var j = 0; j < holeVertices[i].length; j++) {
                var b = holeVertices[i][j];
                flattenedArray.push(b.x);
                flattenedArray.push(b.y);
            }
        }
    }
    var triangulation = earcut(flattenedArray, holeIndexes);
    for (var i = 0; i < triangulation.length; i += 3) {
        result.push([triangulation[i], triangulation[i+1], triangulation[i+2]]);
    }
    return result;
}

function genTriangles(triangleObject, arrayOfVertices, holeVertices) {
    triangleObject.i = triangulate(arrayOfVertices, holeVertices);
    triangleObject.v = arrayOfVertices;
    if (holeVertices) {
        for (var i = 0; i < holeVertices.length; i++) {
            triangleObject.v = triangleObject.v.concat(holeVertices[i]);
        }
    }
    
    var totalPolygonArea = 0;
    var triangleAreas = [];
    for (var j = 0; j < triangleObject.i.length; j++) {
        var area = areaOfTriangle(triangleObject.v, triangleObject.i[j]);
        triangleAreas.push(area);
        totalPolygonArea += area;
    }

    for (var i = 0; i < triangleAreas.length; i++) {
        triangleObject.aR.push(triangleAreas[i]/totalPolygonArea);
    }
}

function drawConnections(distanceThreshold, ctx) {
    for (var i = 0; i < vertices.length; i++) {
        for (var j = i + 1; j < vertices.length; j++) {
            var dist = distanceBetweenDimTwo(vertices[i], vertices[j]);
            if (dist < distanceThreshold) {
                ctx.strokeStyle = '#ffffff';
                ctx.globalAlpha = map_range(dist, 0, distanceThreshold, 0.5, 0);
                ctx.beginPath();
                ctx.moveTo(vertices[i].x, vertices[i].y);
                ctx.lineTo(vertices[j].x, vertices[j].y);
                ctx.stroke();
            }
        }
    }
}

////////////////////////////////////////RUNTIME FUNCTIONS////////////////////////////

function initMeshes() {
    var loader = new THREE.JSONLoader();
    sphereM = new THREE.Mesh(new THREE.SphereGeometry(300, 15, 15));

    var numStars = (canvas.width * canvas.height > 550000) ? 500 : 256;

    for (var i = 0; i < numStars; i++) {
        starFieldM.push({
            x: (Math.random() * canvas.width),
            y: (Math.random() * canvas.height)
        });
        starVelocities.push({
            dx: Math.random() * 0.4 - 0.2,
            dy: Math.random() * 0.4 - 0.2
        });
    }

    // model deets:
    // model2       ellipsoid
    // model3       cube
    // model        some flat random shape
    // sampleModel  building prisms
    // test         this is pretty arbitrary
    // test1        currently a stagborder.

    var stagScale = 200;
    loader.load('./res/models/sBorder.json', function(geometry) {sBorderM = new THREE.Mesh(geometry);sBorderM.scale.x = sBorderM.scale.y = stagScale;});
    loader.load('./res/models/sEye.json', function(geometry) {sEyeM = new THREE.Mesh(geometry);sEyeM.scale.x = sEyeM.scale.y = stagScale;});
    loader.load('./res/models/sEarL.json', function(geometry) {sEarLM = new THREE.Mesh(geometry);sEarLM.scale.x = sEarLM.scale.y = stagScale;});
    loader.load('./res/models/sEarR.json', function(geometry) {sEarRM = new THREE.Mesh(geometry);sEarRM.scale.x = sEarRM.scale.y = stagScale;});
    loader.load('./res/models/sSnout.json', function(geometry) {sSnoutM = new THREE.Mesh(geometry);sSnoutM.scale.x = sSnoutM.scale.y = stagScale;});
}

function startTransition(newStage) {
    _goalPointsSatisfied = [];
    _distanceTravelled = [];
    _goalPoints = [];

    switch(newStage) {
        case STAGE.STARFIELD:
            _goalPoints = starFieldM;
            for (var i = 0; i < 250; i++) {
                _distanceTravelled.push(0);
            }

            if (vertices.length < starFieldM.length) {
                vertices.length = 250;

                for (var i = 250; i < starFieldM.length; i++) {
                    genRandPtOutsideScreen(vertices, "LEFT");
                    _distanceTravelled.push(0);
                }
            }
            break;

        case STAGE.STAG:
            setupStag();
            for (var i = 0; i < starFieldM.length; i++) {
                if (i < sBorderV.length) {
                    _goalPoints.push(sBorderV[i]);
                    if (i >= 1) {
                        _sGoalDistance.push(distanceBetweenDimTwo(
                            _goalPoints[i-1],
                            _goalPoints[i]
                        ));
                    }
                } else {
                    genRandPtOutsideScreen(_goalPoints, "RIGHT");
                }
                _distanceTravelled.push(0);
            }
            break;

    }
    for (var i = 0; i < _goalPoints.length; i++)
        _goalPointsSatisfied.push(false);
    if (_goalPoints.length < vertices.length) {
        vertices.length = _goalPoints.length;
    }
    _stage = STAGE.TRANSITION;
    _newStage = newStage;
    transitionTo(newStage, _goalPoints);
}

function transitionTo(newStage) {
    var transitionComplete = true;
    _goalMovements = [];
    _speeds = [];
    for (var i = 0; i < vertices.length; i++) {
        var diffX = _goalPoints[i].x - vertices[i].x;
        var diffY = _goalPoints[i].y - vertices[i].y;
        var magnitude = sqrt(p(diffX) + p(diffY));
        // (progress == 1) => trip is 100% complete
        var progress = _distanceTravelled[i] / (magnitude + _distanceTravelled[i]);
        var markerOne = 0.3;
        var markerTwo = 0.4;
        var speed = 0;
        var SKIP_SPEEDUP = false;
        var SKIP_SLOWDOWN = false;
        
        if (newStage === STAGE.STARFIELD && i >= 250) {
            SKIP_SPEEDUP = true;
        } else if (newStage === STAGE.STAG && i >= sBorderV.length) {
            SKIP_SLOWDOWN = true;
        }
        
        if (progress < markerOne && !SKIP_SPEEDUP) {
            speed = map_range(progress, 0, markerOne, 0.5, 20);
        } else if (progress <= markerTwo) {
            speed = 20;
        } else if (progress >= markerTwo && !SKIP_SLOWDOWN) {
            speed = map_range(progress, markerTwo, 1, 20, 3);
        } else {
            speed = 20;
        }
        _goalMovements.push({dx: diffX/magnitude * speed,
                             dy: diffY/magnitude * speed});
        _distanceTravelled[i] += speed;
        _speeds.push(speed);
    }
    for (var i = 0; i < vertices.length; i++) {
        if (_goalPointsSatisfied[i] == false) {
            transitionComplete = false;

            if (sqrt(p(_goalPoints[i].x - vertices[i].x) + p(_goalPoints[i].y - vertices[i].y)) > _speeds[i]) {
                vertices[i].x += _goalMovements[i].dx;
                vertices[i].y += _goalMovements[i].dy;
            } else {
                _goalPointsSatisfied[i] = true;
                vertices[i].x = _goalPoints[i].x;
                vertices[i].y = _goalPoints[i].y;
            }
        } else if (_goalPointsSatisfied[i] == true) {
            vertices[i].x = _goalPoints[i].x;
            vertices[i].y = _goalPoints[i].y;
        }
    }
    var closeEnoughChange = true;
    if (newStage == STAGE.STAG && closeEnough > finalcloseEnough)
        closeEnoughChange = false;
    if (transitionComplete && closeEnoughChange) {
        _stage = newStage;

        switch(newStage) {
            case STAGE.STARFIELD:
                sphereM.geometry.dispose();
                sphereM.material.dispose();
                sphereM = undefined;
            break;

            case STAGE.STAG:
                sBorderM.geometry.dispose();
                sBorderM.material.dispose();
                sBorderM = undefined;
                sEyeM.geometry.dispose();
                sEyeM.material.dispose();
                sEyeM = undefined;
                sEarLM.geometry.dispose();
                sEarLM.material.dispose();
                sEarLM = undefined;
                sEarRM.geometry.dispose();
                sEarRM.material.dispose();
                sEarRM = undefined;
                sSnoutM.geometry.dispose();
                sSnoutM.material.dispose();
                sSnoutM = undefined;

                starFieldM = undefined;
                starVelocities = undefined;
                _distanceTravelled = undefined;
                _goalPoints = undefined;
                _goalMovements = undefined;
                _goalPointsSatisfied = undefined;
                _speeds = undefined;
                _newStage = undefined;
                _sFadeIn = undefined;
                _sGoalDistance = undefined;
            break;

        }
    }
}

function renderTransitions(ctx) {
    switch(_newStage) {
        case STAGE.STARFIELD:
            for (var i = 0; i < starFieldM.length; i++) {
                starFieldM[i].x += starVelocities[i].dx;
                starFieldM[i].y += starVelocities[i].dy;
                if (starFieldM[i].x < 0 || starFieldM[i].x > canvas.width)
                    starVelocities[i].dx *= -1;
                if (starFieldM[i].y < 0 || starFieldM[i].y > canvas.height)
                    starVelocities[i].dy *= -1;
                _goalPoints[i] = starFieldM[i];
            }
            break;

        case STAGE.STAG:
            for (var i = 0; i < sBorderV.length; i++) {
                _goalPoints[i] = sBorderV[i];
                if (i < sBorderV.length - 1) {
                    var dist = distanceBetweenDimTwo(vertices[i], vertices[i+1]);
                    if (dist < 70 || dist < _sGoalDistance[i] * 1.001) {
                        ctx.globalAlpha = map_range(dist, 0, 18, 0.8, 0.1) * _sFadeIn;
                        ctx.beginPath();
                        ctx.moveTo(vertices[i].x, vertices[i].y);
                        ctx.lineTo(vertices[i+1].x, vertices[i+1].y);
                        ctx.strokeStyle = '#ffffff';
                        ctx.stroke();
                    }
                }
            }
            if (closeEnough > finalcloseEnough)
                closeEnough -= 0.5;
            if (_sFadeIn <= 1 && closeEnough <= finalcloseEnough + 50)
                _sFadeIn += 0.01;
            break;
    }
    transitionTo(_newStage);
    drawConnections(closeEnough, ctx);
}

function renderSphere(ctx) {
    vertices = [];
    genProjectedVertices(sphereM, vertices);
    drawConnections(closeEnough, ctx);
    sphereM.rotation.x += 0.001;
    sphereM.rotation.y += 0.001;
    sphereM.rotation.z += 0.001;
}

function renderStarfield(ctx) {
    vertices = [];
    for (var i = 0; i < starFieldM.length; i++) {
        starFieldM[i].x += starVelocities[i].dx;
        starFieldM[i].y += starVelocities[i].dy;
        if (starFieldM[i].x < 0 || starFieldM[i].x > canvas.width)
            starVelocities[i].dx *= -1;
        if (starFieldM[i].y < 0 || starFieldM[i].y > canvas.height)
            starVelocities[i].dy *= -1;
        vertices.push(starFieldM[i]);
    }
    drawConnections(closeEnough, ctx);
}

function setupStag() {
    genProjectedVertices(sBorderM, sBorderV);
    genProjectedVertices(sEyeM, sEyeV);
    genProjectedVertices(sEarLM, sEarLV);
    genProjectedVertices(sEarRM, sEarRV);
    genProjectedVertices(sSnoutM, sSnoutV);

    genTriangles(baseTriangles, sBorderV, [sEyeV, sSnoutV]);
    genTriangles(leftEarTriangles, sEarLV);
    genTriangles(rightEarTriangles, sEarRV);

    // 200
    // 600
    // 
    for (var i = 0; i < numInnerStagPts; i++) {
        genRandPtFromTriangles(innerBorderPts, baseTriangles);
        innerBorderPts[i].conn = [];
        var proximity = Math.random() * finalcloseEnough;
        if (proximity < 25) {
            proximity = 25;
        }
        proxThres.push(proximity);

        if (i < 20) {
            genRandPtFromTriangles(leftEarPts, leftEarTriangles);
            genRandPtFromTriangles(rightEarPts, rightEarTriangles);
        }

    }

    // generate connections
    mainStagV = sBorderV.concat(innerBorderPts);
    for (var i = 0; i < innerBorderPts.length; i++) {
        for (var j = i + 1; j < mainStagV.length; j++) {
            var dist = distanceBetweenDimTwo(innerBorderPts[i], mainStagV[j]);
            if (dist < proxThres[i] && !lineSegExitsPolygn(innerBorderPts[i], mainStagV[j], sBorderV)) {
                innerBorderPts[i].conn.push({
                    index: j,
                    alpha: map_range(dist, 0, proxThres[i], 0.5, 0)
                });
            }
        }
    }

    // debug start !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // for (var i = 0; i < 383; i++) {
    //     triangleColors.push('hsl(' + 360 * Math.random() + ', 50%, 50%)');
    // }
    // debug end !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

function renderStag(ctx) {
    vertices = [];

    // debug start !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // tempTriangleDraw(ctx, baseTriangles);
    // tempTriangleDraw(ctx, leftEarTriangles);
    // tempTriangleDraw(ctx, rightEarTriangles);

    // ctx.fillStyle = "#f00"//"#1b1b19"
    // ctx.fillStyle = "white";
    // for (var i = 0; i < innerBorderPts.length; i++) {
    //     var b = innerBorderPts[i];
    //     ctx.fillRect(b.x, b.y, 10, 10);
    // }
    // debug end !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // closeEnough = 45;
    ctx.strokeStyle = '#ffffff';
    for (var i = 0; i < innerBorderPts.length; i++) {
        // connects all inner points to each other
        for (var j = 0; j < innerBorderPts[i].conn.length; j++) {
            ctx.globalAlpha = innerBorderPts[i].conn[j].alpha;
            var point = mainStagV[innerBorderPts[i].conn[j].index];

            ctx.beginPath();
            ctx.moveTo(innerBorderPts[i].x, innerBorderPts[i].y);
            ctx.lineTo(point.x, point.y);
            ctx.stroke();
        }
    }    

    // connects all border points together
    for (var i = 0; i < sBorderV.length - 1; i++) {
        var dist = distanceBetweenDimTwo(sBorderV[i], sBorderV[i+1]);
        ctx.globalAlpha = map_range(dist, 0, 18, 0.8, 0.1);
        ctx.beginPath();
        ctx.moveTo(sBorderV[i].x, sBorderV[i].y);
        ctx.lineTo(sBorderV[i+1].x, sBorderV[i+1].y);
        ctx.strokeStyle = '#ffffff';
        ctx.stroke();
    }

    // EARS
    // connect earpoints
    for (var i = 0; i < leftEarPts.length; i++) {
        for (var j = i + 1; j < leftEarPts.length; j++) {
            var dist = distanceBetweenDimTwo(leftEarPts[i], leftEarPts[j]);
            if (dist < earCloseEnough && true) {
                ctx.strokeStyle = '#ffffff';
                ctx.globalAlpha = map_range(dist, 0, earCloseEnough, 0.5, 0);
                ctx.beginPath();
                ctx.moveTo(leftEarPts[i].x, leftEarPts[i].y);
                ctx.lineTo(leftEarPts[j].x, leftEarPts[j].y);
                ctx.stroke();
            }
        }

        for (var j = 0; j < sEarLV.length; j++) {
            var dist = distanceBetweenDimTwo(leftEarPts[i], sEarLV[j]);
            if (dist < earCloseEnough && true) {
                ctx.strokeStyle = '#ffffff';
                ctx.globalAlpha = map_range(dist, 0, earCloseEnough, 0.5, 0);
                ctx.beginPath();
                ctx.moveTo(leftEarPts[i].x, leftEarPts[i].y);
                ctx.lineTo(sEarLV[j].x, sEarLV[j].y);
                ctx.stroke();
            }
        }
    }

    for (var i = 0; i < rightEarPts.length; i++) {
        for (var j = i + 1; j < rightEarPts.length; j++) {
            var dist = distanceBetweenDimTwo(rightEarPts[i], rightEarPts[j]);
            if (dist < earCloseEnough && true) {
                ctx.strokeStyle = '#ffffff';
                ctx.globalAlpha = map_range(dist, 0, earCloseEnough, 0.5, 0);
                ctx.beginPath();
                ctx.moveTo(rightEarPts[i].x, rightEarPts[i].y);
                ctx.lineTo(rightEarPts[j].x, rightEarPts[j].y);
                ctx.stroke();
            }
        }

        for (var j = 0; j < sEarRV.length; j++) {
            var dist = distanceBetweenDimTwo(rightEarPts[i], sEarRV[j]);
            if (dist < earCloseEnough && true) {
                ctx.strokeStyle = '#ffffff';
                ctx.globalAlpha = map_range(dist, 0, earCloseEnough, 0.5, 0);
                ctx.beginPath();
                ctx.moveTo(rightEarPts[i].x, rightEarPts[i].y);
                ctx.lineTo(sEarRV[j].x, sEarRV[j].y);
                ctx.stroke();
            }
        }
    }

    // eye
    ctx.fillStyle = "#1b1b19";
    tempFill(ctx, sEyeV);
    // snout
}

function tempTriangleDraw(ctx, triObj) {
    for (var j = 0; j < triObj.i.length; j++) {
        ctx.fillStyle = triangleColors[j];
        ctx.globalAlpha = 1;
        ctx.beginPath();
        ctx.moveTo(triObj.v[triObj.i[j][0]].x, triObj.v[triObj.i[j][0]].y);
        ctx.lineTo(triObj.v[triObj.i[j][1]].x, triObj.v[triObj.i[j][1]].y);
        ctx.lineTo(triObj.v[triObj.i[j][2]].x, triObj.v[triObj.i[j][2]].y);
        ctx.closePath();
        ctx.fill();
        ctx.strokeStyle = '#ffff00';
        ctx.stroke();
    }
}

function tempFill(ctx, modelVertices) {
    ctx.beginPath();
    ctx.globalAlpha = 1;
    for (var i = 0; i < modelVertices.length; i++) {
        ctx.lineTo(modelVertices[i].x, modelVertices[i].y);
        // ctx.fillRect(b.x, b.y, 1, 1);
    }
    ctx.closePath();
    ctx.fill();
}

////////////////////////////////////////CREATING OBJECTS/////////////////////////////

var setup = function () {
    renderer.setSize( vw, vh );
    container = document.createElement( 'div' );
    document.body.appendChild( container );
    canvas = document.getElementById("twoDimCanvas");
    canvas.width = vw;
    canvas.height = vh;
    stats = new Stats();                    //Generate FPS counter
    container.appendChild( stats.dom );
    starFieldM = [];
    starVelocities = [];
    initMeshes();
}

////////////////////////////////////////RENDERING & ANIMATING/////////////////////////

var render = function () {
    renderID = window.requestAnimationFrame( render );
    stats.update();    //Update FPS counter.
    var ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    switch(_stage) {
        case STAGE.TRANSITION:
            renderTransitions(ctx);
            break;

        case STAGE.SPHERE:
            renderSphere(ctx);
            break;

        case STAGE.STARFIELD:
            renderStarfield(ctx)
            break;

        case STAGE.STAG:
            renderStag(ctx);
            break;
    }

    var timeElapsed = Date.now() - startTime;                       //8000, 18000.   1000, 5000.  2000, 7000
    if (timeElapsed > 2000 && _stage == STAGE.SPHERE)
        startTransition(STAGE.STARFIELD);
    else if (timeElapsed > 1000 && _stage == STAGE.STARFIELD)
        startTransition(STAGE.STAG);
    renderer.render(scene, camera);
};

////////////////////////////////////////RUN/////////////////////////

// THREE.DefaultLoadingManager.onProgress = function ( item, loaded, total ) {
//     console.log(item, loaded, total);
// };

THREE.DefaultLoadingManager.onLoad = function() {
    startTime = Date.parse(new Date());
    // generateTriangles();

    render();
}

setup();

// cancelAnimationFrame( renderID );