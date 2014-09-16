/*A program that uses a single asynchronous filesystem operation to 
read a file and print the number of newlines it contains to the 
console (stdout), similar to running cat file | wc -l.
*/

var fs = require('fs');
var array = [];
var hurr = new Buffer(array);
//console.log((((fs.readFileSync(process.argv[2])).toString()).split('\n')).length - 1);
fs.readFile(process.argv[2], function(err, hurr) {
	if (err) throw err;
	console.log(hurr.toString().split('\n').length - 1); 
});

/*Official solution

    var fs = require('fs')
    var file = process.argv[2]
    
    fs.readFile(file, function (err, contents) {
      // fs.readFile(file, 'utf8', callback) can also be used
      var lines = contents.toString().split('\n').length - 1
      console.log(lines)
    })
*/