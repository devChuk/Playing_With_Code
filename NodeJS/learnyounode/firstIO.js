//A program that uses a single synchronous filesystem operation to read a file and print the number of newlines it contains to the console (stdout), similar to running cat file | wc -l.

var fs = require('fs');
console.log((((fs.readFileSync(process.argv[2])).toString()).split('\n')).length - 1);
//one line magic gogo LOL