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


