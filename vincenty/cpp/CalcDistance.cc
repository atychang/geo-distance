/*
 * Calculates the distance of two points (from, to) in meter, using latitude and longitude, using Vincenty's formulae(inverse solution).
 * Reference:
 * 1. http://www.movable-type.co.uk/scripts/latlong-vincenty.html
 * 2. http://en.wikipedia.org/wiki/Vincenty's_formulae
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
    double a = 6378137.0;   // meter
    double f = 1 / 298.257223563;
    double b = (1 - f) * a; // meter
    double U1 = atan((1 - f) * tan(toRadians(lat1)));
    double U2 = atan((1 - f) * tan(toRadians(lat2)));
    double sinU1 = sin(U1), cosU1 = cos(U1);
    double sinU2 = sin(U2), cosU2 = cos(U2);
    double L = toRadians(lon2 - lon1);

    double sinLambda;
    double cosLambda;
    double sinSigma;
    double cosSigma;
    double sigma;
    double cosSqAlpha;
    double cos2SigmaM;

    double lambda = L, prevLambda;
    int iterationLimit = 100;

    /* 
     * Iteratively evaluate the following equations until
     * lambda converges has converged to the desired degree of accuracy
     * (corresponds to approximately 0.06mm)
     */
    do {
        sinLambda = sin(lambda);
        cosLambda = cos(lambda);;
        sinSigma = sqrt(pow(cosU2 * sinLambda, 2) + pow(cosU1 * sinU2 - sinU1 * cosU2 * cosLambda, 2));

        if (sinSigma == 0)  // coincident points
            return 0;

        cosSigma = sinU1 * sinU2 + cosU1 * cosU2 * cosLambda;
        sigma = atan(sinSigma / cosSigma);
        double sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
        cosSqAlpha = 1 - pow(sinAlpha, 2);
    
        if (cosSqAlpha == 0)    // equatorial line: cosSqAlpha = 0
            cos2SigmaM = 0;    
        else
            cos2SigmaM = cosSigma - 2 * sinU1 * sinU2 / cosSqAlpha;

        double C = f / 16 * cosSqAlpha * (4 + f * (4 - 3 * cosSqAlpha));
        prevLambda = lambda;
        lambda = L + (1 - C) * f * sinAlpha * (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * (-1 + 2 * pow(cos2SigmaM, 2))));
    } while (std::abs(lambda - prevLambda) > 1e-12 && --iterationLimit > 0);

    if (iterationLimit == 0)    // formula failed to converge
        return 0;

    double uSq = cosSqAlpha * (pow(a, 2) - pow(b, 2)) / pow(b, 2);
    double A = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)));
    double B = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));
    double deltaSigma = B * sinSigma * (cos2SigmaM + B / 4 * (cosSigma * (-1 + 2 * pow(cos2SigmaM, 2)) - B / 6 * cos2SigmaM * (-3 + 4 * pow(sinSigma, 2)) * (-3 + 4 * pow(cos2SigmaM, 2))));
    
    double s = b * A * (sigma - deltaSigma);    // in the same units as a and b

    // bearing (direction) in radius
    // degree = radius * 180 / pi
    double revAz = atan2(cosU1 * sinLambda, -sinU1 * cosU2 + cosU1 * sinU2 * cosLambda);
    std::cout << revAz << std::endl;    // 2.21113 radians
    
    return s;
}

int main(int argc, char * argv[]) {
    std::cout << getDistance(23.205402, 120.335066, 23.202188, 120.339733) << std::endl;    // 595.7683677122474 m

    return 0;
}
