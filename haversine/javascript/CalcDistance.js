/*
 * Calculate the distance of two points (from, to) in meter, using latitude and longitude, using Haversine formula.
 * Reference:
 * 1. https://en.wikipedia.org/wiki/Haversine_formula
 */

function toRadians(degree) {
    return degree * Math.PI / 180;
}

function getDistance(lat1, lon1, lat2, lon2) {
    var r = 6378137.0;	// meter

    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    var dlat = lat2 - lat1;
    var dlon = lon2 - lon1;

    var d = 2 * r * Math.asin(Math.sqrt(Math.pow(Math.sin(dlat / 2), 2) + Math.cos(lat1) * Math.cos(lat2) * Math.pow(Math.sin(dlon / 2), 2)));

	return d;
}
