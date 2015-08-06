


// CED subroutine for cleaning up JavaScript rounding errors 

// to any reasonable number of decimal places 5/5/1997 last mod 2/19/2004

// round for decimal of (value of precision) places, default is 3

// This routine can be used to pass a number and a number for precision

// or just a number only, that is to be rounded to a set number of decimal

// places. This routine supports leading and training zeros, leading and

// trailing spaces, and padding. To prevent errors, pass variables as a string.



  function perRound(num, precision) {

	var precision = 2; //default value if not passed from caller, change if desired

	// remark if passed from caller

	precision = parseInt(precision); // make certain the decimal precision is an integer

    var result1 = num * Math.pow(10, precision);

    var result2 = Math.round(result1);

    var result3 = result2 / Math.pow(10, precision);

    return zerosPad(result3, precision);

}



  function zerosPad(rndVal, decPlaces) {

    var valStrg = rndVal.toString(); // Convert the number to a string

    var decLoc = valStrg.indexOf("."); // Locate the decimal point

    // check for a decimal 

    if (decLoc == -1) {

        decPartLen = 0; // If no decimal, then all decimal places will be padded with 0s

        // If decPlaces is greater than zero, add a decimal point

        valStrg += decPlaces > 0 ? "." : "";

    }

    else {

        decPartLen = valStrg.length - decLoc - 1; // If there is a decimal already, only the needed decimal places will be padded with 0s

    }

     var totalPad = decPlaces - decPartLen;    // Calculate the number of decimal places that need to be padded with 0s

    if (totalPad > 0) {

        // Pad the string with 0s

        for (var cntrVal = 1; cntrVal <= totalPad; cntrVal++) 

            valStrg += "0";

        }

    return valStrg;

}

// send the value in as "num" in a variable



// clears field of default value

  function clear_field(field) {

		if (field.value==field.defaultValue) {

			field.value=''

		}

	}



  function fclear(form)

  {

        form.deg.value = ""

        form.latmeters.value = ""

        form.latfeet.value = ""

        form.latnm.value = ""

        form.latsm.value = ""

        form.longmeters.value = ""

        form.longfeet.value =""

        form.longnm.value = ""

        form.longsm.value = ""

        form.latmetersr.value = ""

        form.latfeetr.value = ""

        form.latnmr.value = ""

        form.latsmr.value = ""

        form.longmetersr.value = ""

        form.longfeetr.value =""

        form.longnmr.value = ""

        form.longsmr.value = ""

  }



  function deg2rad(deg)

  {

	conv_factor = (2.0 * Math.PI)/360.0;

	return(deg * conv_factor);

  }



  function rad2deg(rad)

  {

	conv_factor = 360/(2.0 * Math.PI);

	return(rad * conv_factor);

  }



	function log10(val)  // calculate the log base 10 of val

	{ return(Math.LOG10E * Math.log(val)); }



	function compute(obj) // Compute lengths of degrees

	{

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

		

		// Place values in output fields

		obj.latmeters.value = (latlen);

		obj.latfeet.value = (latlen * (3.280833333));

		obj.latsm.value = obj.latfeet.value / 5280;

		obj.latnm.value = obj.latsm.value / 1.15077945;

		obj.longmeters.value = (longlen);

		obj.longfeet.value = (longlen * (3.280833333)   );

		obj.longsm.value = obj.longfeet.value / 5280;

		obj.longnm.value = obj.longsm.value / 1.15077945;

		obj.latmetersr.value = perRound(latlen);

		obj.latfeetr.value = perRound(latlen * (3.280833333));

		obj.latsmr.value = perRound(obj.latfeet.value / 5280);

		obj.latnmr.value = perRound(obj.latsm.value / 1.15077945);

		obj.longmetersr.value = perRound(longlen);

		obj.longfeetr.value = perRound(longlen * (3.280833333));

		obj.longsmr.value = perRound(obj.longfeet.value / 5280);

		obj.longnmr.value = perRound(obj.longsm.value / 1.15077945);



	}



