#pragma once  // Ensures header file is included only once during compilation

#include <cmath>  // Include cmath for mathematical functions

namespace geo {

// Structure to represent geographic coordinates (latitude and longitude)
struct Coordinates {
    double lat;  // Latitude
    double lng;  // Longitude

    // Comparison operator to check equality of Coordinates
    bool operator==(const Coordinates& other) const {
        return lat == other.lat && lng == other.lng;
    }

    // Comparison operator to check inequality of Coordinates
    bool operator!=(const Coordinates& other) const {
        return !(*this == other);
    }
};

/**
 * Computes the great-circle distance between two geographic coordinates using the Haversine formula.
 * @param from Starting coordinates
 * @param to Target coordinates
 * @return Distance in meters between 'from' and 'to'
 */
double ComputeDistance(Coordinates from, Coordinates to);

}  // namespace geo
