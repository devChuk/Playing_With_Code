/*
a program that prints a list of files in a given directory, filtered by the 
extension of the files. You will be provided a directory name as the first 
argument to your program (e.g. '/path/to/dir/') and a file extension to 
filter by as the second argument.

For example, if you get 'txt' as the second argument then you will need to 
filter the list to only files that end with .txt.

The list of files should be printed to the console, one file per line. 
You must use asynchronous I/O.
*/

var fs = require('fs');
var array = [];
var filter = false;
if (process.argv[3])
	filter = true;
//console.log((((fs.readFileSync(process.argv[2])).toString()).split('\n')).length - 1);
fs.readdir(process.argv[2], function(err, array) {
	if (err) throw err;
	for (var i = 0; i < array.length; i++) {
		if (filter) {
			if (array[i].indexOf("." + process.argv[3]) != -1)
				console.log(array[i]);
			}
		else {
			console.log(array[i]);
		}
	}
});

/*Official solution
var fs = require('fs')
var path = require('path')

fs.readdir(process.argv[2], function (err, list) {
  list.forEach(function (file) {
    if (path.extname(file) === '.' + process.argv[3])
      console.log(file)
  })
})
*/