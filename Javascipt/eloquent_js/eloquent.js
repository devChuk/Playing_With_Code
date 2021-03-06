function greaterThan(num) {
 return function(y) {
    return y > 1;
  };
}

var greaterThanTen = greaterThan(10);
//console.log(greaterThanTen(9));



var set = {"Spot": true};
set["White Fang"] = true;
delete set["Spot"];
//console.log("LuLu" in set);


function range(num) {
	var list = new Array();
	for (var i = 0; i <= num; i++)
		list.push(i);
	list.forEach(function(entry) {
		console.log(entry)
	});
}
//console.log(range(10));


function startsWith(word,prefix) {
	return (word.slice(0,prefix.length) == prefix);
}

function catNames(paragraph) {
  var colon = paragraph.indexOf(":");
  return paragraph.slice(colon + 2).split(", ");
}

/*
var paragraph = "born 20/09/2004 (mother Yellow Bess): " +
              	"    Doctor Hobbles the 2nd, Noog"
console.log(paragraph);
console.log("PROCESSING");
console.log(catNames(paragraph));
*/
//lol how can
//var paragraph = "died 27/04/2006: Black Leclère";

function extractDate(paragraph) {
	function cookiecut(start,length) {
		return Number(paragraph.slice(start, start + length));
	}
	return new Date(cookiecut(11,4),cookiecut(8,2),cookiecut(5,2));
}
//console.log(extractDate(paragraph));

function between(string, start, end) {
	var startAt = string.indexOf(start) + start.length;
  	var endAt = string.indexOf(end, startAt);
  	return string.slice(startAt, endAt);
  }
//console.log(between("bu ] boo [ bah ] gzz", "[ ", " ]"));

function formatDate(date) {
  function pad(number) {
    if (number < 10)
      return "0" + number;
    else
      return number;
  }
  return pad(date.getDate()) + "/" + pad(date.getMonth() + 1) +
             "/" + date.getFullYear();
}
//SOMETHING TO REMEMBER:
//If there's a pattern, put a function in a function.

function oldestCat(info) {
	var oldest = null;

	for (var name in info) {
    var cat = info[name];
    if (!("death" in cat) &&
        (oldest == null || oldest.birth > cat.birth))
      oldest = cat;
  }
  	if (oldest == null)
    return null;
  else
    return oldest.name;
}

function ranger(num, num2) {
	var start, end;
	if (arguments.length < 2) {
		num2 = num;
		num = 0;
	}
	
	var list = new Array();
	for (var i = num; i <= num2; i++)
			list.push(i);
	list.forEach(function(entry) {
		console.log(entry)
	});
}

function sum(numbers) {
	var total = 0;
	for (var i = 0; i<numbers.length;i++)
		total += numbers[i];
	return total;
}

//CHAPTER 5
//ERROR HANDLING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//LOL THERE ARE NO EXERCISES

//CHAPTER 6
//FUNCTIONAL PROGRAMMING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

function reduce(combine, base, array) {
  forEach(array, function (element) {
    base = combine(base, element);
  });
  return base;
}

function countZeroes(numbers) {
  function counter(total, element) {
    return total + (element === 0 ? 1 : 0);
  }
  return reduce(counter, 0, numbers);
}

function count(test,array) {
  return reduce(function(total, element) {
    return total + (test(element) ? 1 : 0);
  }, 0, array);
}

function processParagraph(paragraph) {
  var header = 0;
  while (paragraph.charAt(0) == "%") {
    paragraph = paragraph.slice(1);
    header++;
  }

  return {type: (header == 0 ? "p" : "h" + header), //the ? mark is an inline if statement. pretty neat eh?
          content: paragraph};                      //basically if (header == 0), set type to "p". Else, return hX.
}                                                                                                             //where X = # of %s

function splitParagraph(paragraph) {

  function indexOrEnd(character) {                  //returns the index of a character inside text
    var index = text.indexOf(character);            //if not found, return the length of the text (the end basically)
    return index == -1 ? text.length : index;
  }

  function takeNormal() {                           
    var end = reduce(Math.min, text.length,         //find the length of the text. find the index of the firstmost * or {. The lesser one becomes the End.
                     map(indexOrEnd, ["*", "{"]));  
    var part = text.slice(0, end);                  //slice off from beginning to end
    text = text.slice(end);                         //set text to the fragments left behind
    return part;                                    //it's self-explanatory fool
  }

  function takeUpTo(character) {
    var end = text.indexOf(character, 1);           //the second parameter states where to start the search. This way you won't find an initial * or {}
    if (end == -1)                                  //if not found. the writer has dun goof
      throw new Error("Missing closing '" + character + "'");
    var part = text.slice(1, end);                  //otherwise, same as before.
    text = text.slice(end + 1);
    return part;
  }

  var fragments[];                                  //Fragments are divided by *, {, or }. Yup. It's pretty simple.

  while (paragraph != "") {
    if (text.charAt(0) == "*") {
      fragments.push({type: "emphasized",
                      content: takeUpTo("*")});
    }
    else if (text.charAt(0) == "{") {
      fragments.push({type: "footnote",
                      content: takeUpTo("}")});
    }
    else {
      fragments.push({type: "normal",
                      content: takeNormal()});
    }
  }
}

function tag(name, content, attributes) {
  return {name: name, attributes: attributes, content: content};
}

function image(src) {
  return tag("img", [], {src: src});
}

function footnote(number) {
  return tag("sup", [link("#footnote" + number,
                          String(number))]);
}

function renderParagraph(paragraph) {
  return tag(paragraph.type, map(renderFragment,
                                  paragraph.content));
}

function renderfragment(fragment) {
  if (fragment.type == "reference")
    return footnote(fragment.number);
  else if (fragment.type == "emphasized")
    return tag("em", [fragment.content]);
  else
    return fragment.content;
}

//CHAPTER 7
//SEARCHING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

function makeRoad(from, to, length) {
  function addRoad(from, to) {
    if (!(from in roads))
      roads[from] = [];
    roads[from].push({to: to, distance: length});
  }
  addRoad(from, to);
  addRoad(to, from);
}

function makeRoads(start) {
  for (var i = 0; i < arguments.length, i += 2)
  makeRoad(start, arguments[i], arguments[i + 1]; 
}

function member(array, value) {
  var found = false;
  forEach(array, function(element) {
    if (element === value)
      found = true;
  });
  return found;
}

function filter(test, array) {
  var results = [];
  for (var i = 0; i < array.length; i++) {
    if (test(array[i]))
      results.push(array[i]);

  return results;
  }
}

function possibleRoutes(from, to) {
  function findRoutes(route) {
    function notVisited(road) {
      return !member(route.places, road.to);
    }
    function continueRoute(road) {
      return findRoutes({places: route.places.concat([road.to]),
                         length: route.length + road.distance});
    }

    var end = route.places[route.places.length - 1];
    if (end == to)
      return [route];
    else
      return flatten(map(continueRoute, filter(notVisited,
                                               roadsFrom(end))));
  }
  return findRoutes({places: [from], length: 0});
}

function shortestRoute(from, to) {
  var options = possibleRoutes(from, to);
  var min = options[0];
  for (var i = 1; i < options.length; i++) {
    if (min.length > options[i].length) {
      min = options[i];
    }
  }
  return min;
}

function weightedDistance(pointA, pointB) {
  if (!(Math.abs(pointA.x - pointB.x) == 1) || (Math.abs(pointA.y - pointB.y) == 1))
    console.log("Error. Looks like these points aren't even touching, fool.")
    return null
  var heightDifference = heightAt(pointB) - heightAt(pointA);
  var climbFactor = (heightDifference < 0 ? 1 : 2);
  var flatDistance = (pointA.x == pointB.x || pointA.y == pointB.y ? 100 : 141);
  return flatDistance + climbFactor * Math.abs(heightDifference);
}

function point(x, y) {
  return {x: x, y: y};
}

function addPoints(a, b) {
  return point(a.x + b.x, a.y + b.y);
}

function samePoint(a, b) {
  return a.x == b.x && a.y == b.y;
}

function possibleDirections(a) {
  
  function insideMap(point) {
    return point.x >= 0 && point.x < mapSize &&
           point.y >= 0 && point.y < mapSize;
  }

  var results = [];
  for (var i = -1; i <= 1; i++)
    for (var j = -1; j <= 1; j++) {
      var hurr = point(a.x + i, a.y + j);
      if (insideMap(hurr))
        results.push(hurr);
  }
  return results;
}
//places: {} 
//length: #