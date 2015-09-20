/*
 * Calculate the distance of two points (from, to) in meter, using latitude and longitude, using Vincenty's formula(inverse solution).
 * Reference:
 * 1. http://www.movable-type.co.uk/scripts/latlong-vincenty.html
 * 2. http://en.wikipedia.org/wiki/Vincenty's_formulae
 */

function toRadians(degree) {
    return degree * Math.PI / 180;
}

function getDistance(lat1, lon1, lat2, lon2) {
    var a = 6378137.0;	// meter
	var f = 1 / 298.257223563;
	var b = (1 - f) * a;	// meter
	var U1 = Math.atan((1 - f) * Math.tan(toRadians(lat1)));
	var U2 = Math.atan((1 - f) * Math.tan(toRadians(lat2)));
	var sinU1 = Math.sin(U1), cosU1 = Math.cos(U1);
	var sinU2 = Math.sin(U2), cosU2 = Math.cos(U2);
	var L = toRadians(lon2 - lon1);

	var sinLambda;
	var cosLambda;
	var sinSigma;
	var cosSigma;
	var sigma;
	var cosSqAlpha;
	var cos2SigmaM;
		
	var lambda = L, prevLambda;
	var iterationLimit = 100;
		
	/* 
	 * Iteratively evaluate the following equations until
	 * lambda converges has converged to the desired degree of accuracy
	 * (corresponds to approximately 0.06mm)
	 */
	do {
		sinLambda = Math.sin(lambda);
		cosLambda = Math.cos(lambda);;
		sinSigma = Math.sqrt(Math.pow(cosU2 * sinLambda, 2) + Math.pow(cosU1 * sinU2 - sinU1 * cosU2 * cosLambda, 2));

		if (sinSigma == 0)  // coincident points
			return 0;

		cosSigma = sinU1 * sinU2 + cosU1 * cosU2 * cosLambda;
		sigma = Math.atan(sinSigma / cosSigma);
		var sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
		cosSqAlpha = 1 - Math.pow(sinAlpha, 2);

		if (cosSqAlpha == 0)    // equatorial line: cosSqAlpha = 0
			cos2SigmaM = 0;
        else
            cos2SigmaM = cosSigma - 2 * sinU1 * sinU2 / cosSqAlpha;
			
        var C = f / 16 * cosSqAlpha * (4 + f * (4 - 3 * cosSqAlpha));
		prevLambda = lambda;
		lambda = L + (1 - C) * f * sinAlpha * (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * (-1 + 2 * Math.pow(cos2SigmaM, 2))));
	} while (Math.abs(lambda - prevLambda) > 1e-12 && --iterationLimit > 0);

	if (iterationLimit == 0)	// formula failed to converge
		return 0;

	var uSq = cosSqAlpha * (Math.pow(a, 2) - Math.pow(b, 2)) / Math.pow(b, 2);
	var A = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)));
	var B = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));
	var deltaSigma = B * sinSigma * (cos2SigmaM + B / 4 * (cosSigma * (-1 + 2 * Math.pow(cos2SigmaM, 2)) - B / 6 * cos2SigmaM * (-3 + 4 * Math.pow(sinSigma, 2)) * (-3 + 4 * Math.pow(cos2SigmaM, 2))));

	var s = b * A * (sigma - deltaSigma);	// in the same units as a and b

	// bearing (direction) in radius
	// degree = radius * 180 / pi
	var revAz = Math.atan2(cosU1 * sinLambda, -sinU1 * cosU2 + cosU1 * sinU2 * cosLambda);		
	console.log(revAz);  // 2.21113 radians

	return s;
}
