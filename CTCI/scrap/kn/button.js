// Brian Chuk

function flatten(arr) {
  var result = [];
  for (var i = 0; i < arr.length; i++) {
  	if (arr[i] instanceof Array) {
  		result = result.concat(flatten(arr[i]));
  	} else if (arr[i] != null) { 
  		result.push(arr[i]);
  	}
  }
  return result;
}

var test1 = [0, 2, [[2, 3], 8, 100, null, [[null]]], -2];
var test2 = [];
var test3 = [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[1]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]];
var test4 = [1, [2, [3, [4]]]];

console.log("Test Case 1:\n");
console.log(test1);
console.log(flatten(test1));
console.log("\n");
// [0, 2, 2, 3, 8, 100, -2]

console.log("Test Case 2:\n");
console.log(test2);
console.log(flatten(test2));
console.log("\n");
// []

console.log("Test Case 3:\n");
console.log(test3);
console.log(flatten(test3));
console.log("\n");
// [1]

console.log("Test Case 4:\n");
console.log(test4);
console.log(flatten(test4));
console.log("\n");
// [1, 2, 3, 4]