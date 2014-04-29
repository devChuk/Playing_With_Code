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

