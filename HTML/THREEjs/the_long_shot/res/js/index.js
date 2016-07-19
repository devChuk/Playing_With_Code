/*
Title:			BrianCh.uk Home Screen Javascript v1
Author:			Brian Chuk (brianch.uk)
Copyright: 		2015, Brian Chuk - All rights reserved (you have permission to use it, just tell me :D)
*/
var mobile = false;
	if (window.innerWidth <= 767) {
		mobile = true;
	}

var animated = true;
if (window.innerWidth > 991) {
	var hack_the_city = document.createElement('script');
	hack_the_city.src = './res/js/bleh.js';
	hack_the_city.type = 'text/javascript';
	document.body.appendChild(hack_the_city);
}
else {animated = false;}

$( window ).resize(function() {
	
	if (!animated && window.innerWidth > 991) {
		var hack_the_city = document.createElement('script');
		hack_the_city.src = './res/js/bleh.js';
		hack_the_city.type = 'text/javascript';
		document.body.appendChild(hack_the_city);
		animated = true;
	}
});