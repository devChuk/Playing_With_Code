function myFunction(p1, p2) {
    return p1 * p2;              // The function returns the product of p1 and p2
}

for (i = 0; i < cars.length; i++) { 
    text += cars[i] + "<br>";
}

var person = {fname:"John", lname:"Doe", age:25}; 

var text = "";
var x;
for (x in person) {
    text += person[x];
}

while (i < 10) {
    text += "The number is " + i;
    i++;
}

do {
    text += "The number is " + i;
    i++;
}
while (i < 10);

break;
console.log("lol");


var length = 16;                               // Number
var lastName = "Johnson";                      // String
var cars = ["Saab", "Volvo", "BMW"];           // Array
var x = {firstName:"John", lastName:"Doe"};    // Object
var ay = true;								   // Bool
var me = undefined;

var txt = "ay";
txt.length;
txt.indexOf("a");
txt.lastIndexOf("a");


var str = "Apple, Banana, Kiwi";
var res = str.slice(7,13);
var res = str.substring(7,13);

str = "Please visit Microsoft!";
var n = str.replace("Microsoft","W3Schools");

var text1 = "Hello World!";       // String
var text2 = text1.toUpperCase();  // text2 is text1 converted to upper
text1.toLowerCase();

var text = "Hello" + " " + "World!";
var text = "Hello".concat(" ","World!");

var str = "HELLO WORLD";
str.charAt(0);            // returns H
str.charCodeAt(0);         //	returns 72

var txt = "a,b,c,d,e";   // String
txt.split(",");          // Split on commas


var fruits = [];
fruits.toString();
fruits.join(" * ");
fruits.pop(); fruits.push();
fruits.shift(); fruits.unshift();
fruits[0] = "Kiwi";
fruits.splice(2, 0, "Lemon", "Kiwi");
var myChildren = myGirls.concat(myBoys);
var citrus = fruits.slice(3);

fruits.sort();				//alphabetical only, like strings
fruits.reverse();
points.sort(function(a, b){return a - b});




switch (new Date().getDay()) {
    case 0:
        day = "Sunday";
        break;
    case 1:
        day = "Monday";
        break;
    case 2:
        day = "Tuesday";
        break;
    case 3:
        day = "Wednesday";
        break;
    case 4:
        day = "Thursday";
        break;
    case 5:
        day = "Friday";
        break;
    case 6:
        day = "Saturday";
}


person.lastName;
person["lastName"];

