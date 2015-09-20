/*
 * Calculates the distance of two points (from, to) in meter, using latitude and longitude, using Haversine formula.
 * Reference:
 * 1. https://en.wikipedia.org/wiki/Haversine_formula
 *
 * Compile:
 *     $ g++ CalcDistance.cc -o CalcDistance
 * Run:
 *     $ ./CalcDistance
 */

#include <iostream>
#include <cmath>

double toRadians(double degree) {
    return degree * M_PI / 180;
}

double getDistance(double lat1, double lon1, double lat2, double lon2) {
    double r = 6378137.0;   // earth radius in meter
    
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double d = 2 * r * asin(sqrt(pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2)));

    return d;
}

int main(int argc, char * argv[]) {
    std::cout << getDistance(23.205402, 120.335066, 23.202188, 120.339733) << std::endl;    // 596.671 m

    return 0;
}
