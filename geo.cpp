#define _USE_MATH_DEFINES  // Define to ensure math constants like M_PI are available
#include "geo.h"           // Include necessary headers
#include <cmath>           // Include cmath for mathematical functions

namespace geo {

/**
 * Computes the great-circle distance between two geographic coordinates using the Haversine formula.
 * @param from Starting coordinates
 * @param to Target coordinates
 * @return Distance in meters between 'from' and 'to'
 */
double ComputeDistance(Coordinates from, Coordinates to) {
    using namespace std;  // Use standard namespace for sin, cos, abs, etc.
    
    if (from == to) {
        return 0;  // If coordinates are the same, distance is zero
    }
    
    static const double dr = M_PI / 180.;  // Conversion factor from degrees to radians
    static const int earth_rd = 6371000;   // Earth's radius in meters
    
    // Haversine formula for calculating great-circle distance
    return acos(sin(from.lat * dr) * sin(to.lat * dr)
                + cos(from.lat * dr) * cos(to.lat * dr) * cos(abs(from.lng - to.lng) * dr))
           * earth_rd;
}

} // namespace geo
