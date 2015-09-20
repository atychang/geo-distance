/*
 * Calculate the distance of two points (from, to) in meter, using latitude and longitude, using Haversine formula.
 * Reference:
 * 1. https://en.wikipedia.org/wiki/Haversine_formula
 */

public class CalcDistance {
	public static double getDistance(double lat1, double lon1, double lat2, double lon2) {
		double r = 6378137.0;	// earth radius in meter

        lat1 = Math.toRadians(lat1);
        lon1 = Math.toRadians(lon1);
        lat2 = Math.toRadians(lat2);
        lon2 = Math.toRadians(lon2);

        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;

        double d = 2 * r * Math.asin(Math.sqrt(Math.pow(Math.sin(dlat / 2), 2) + Math.cos(lat1) * Math.cos(lat2) * Math.pow(Math.sin(dlon / 2), 2)));

		return d;
	}

    public static void main(String[] args) {
		System.out.println(getDistance(23.205402, 120.335066, 23.202188, 120.339733));	// 596.6710070527057 m
	}
}
