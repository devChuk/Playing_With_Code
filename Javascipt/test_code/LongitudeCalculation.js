// CED subroutine for cleaning up JavaScript rounding errors 
// to any reasonable number of decimal places 5/5/1997 last mod 2/19/2004
// round for decimal of (value of precision) places, default is 3
// This routine can be used to pass a number and a number for precision
// or just a number only, that is to be rounded to a set number of decimal
// places. This routine supports leading and training zeros, leading and
// trailing spaces, and padding. To prevent errors, pass variables as a string.



function deg2rad(deg) {
	conv_factor = (2.0 * Math.PI)/360.0;
	return(deg * conv_factor);
}

function rad2deg(rad) {
	conv_factor = 360/(2.0 * Math.PI);
	return(rad * conv_factor);
}

function log10(val) { // calculate the log base 10 of val
  return(Math.LOG10E * Math.log(val));
}

function compute(obj) {// Compute lengths of degrees
	// Convert latitude to radians
	lat = deg2rad(obj.deg.value);
	// Set up "Constants"
	m1 = 111132.92;		// latitude calculation term 1
	m2 = -559.82;		// latitude calculation term 2
	m3 = 1.175;			// latitude calculation term 3
	m4 = -0.0023;		// latitude calculation term 4
	p1 = 111412.84;		// longitude calculation term 1
	p2 = -93.5;			// longitude calculation term 2
	p3 = 0.118;			// longitude calculation term 3

	// Calculate the length of a degree of latitude and longitude in meters

	latlen = m1 + (m2 * Math.cos(2 * lat)) + (m3 * Math.cos(4 * lat)) +
  (m4 * Math.cos(6 * lat));
  longlen = (p1 * Math.cos(lat)) + (p2 * Math.cos(3 * lat)) +
  (p3 * Math.cos(5 * lat));
}