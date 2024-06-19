#pragma once // Ensures header file is included only once during compilation

#include "geo.h" // Include necessary headers

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

namespace transport {

    // Struct representing a stop in the transportation system
    struct Stop {
        std::string name;                   // Name of the stop
        geo::Coordinates coordinates;       // Geographic coordinates of the stop
        std::set<std::string> buses_by_stop; // Set of bus numbers passing through this stop
    };

    // Struct representing a bus in the transportation system
    struct Bus {
        std::string number;                     // Bus number or identifier
        std::vector<const Stop*> stops;         // Vector of stops on the bus route
        bool is_circle;                         // Indicates if the bus route is circular
    };

    // Struct holding statistical information about a bus route
    struct BusStat {
        size_t stops_count;             // Total number of stops on the route
        size_t unique_stops_count;      // Number of unique stops (no duplicates)
        double route_length;            // Total length of the bus route
        double curvature;               // Curvature (complexity) of the bus route
    };

} // namespace transport

