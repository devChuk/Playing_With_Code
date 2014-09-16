//A program that accepts one or more numbers as command-line arguments and prints the sum of those numbers to the console (stdout).
//console.log(process.argv);

function sumAll(args) {
	var sum = 0;
	for (i = 2; i < args.length; i++) {
			sum += parseInt(args[i]);
	}
	return sum;
}


console.log(sumAll(process.argv));