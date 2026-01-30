#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

const double EARTH_RADIUS = 6371.0;

struct CityCoords {
    string name;
    double latitude;
    double longitude;

    CityCoords(string n, double lat, double lon)
        : name(n), latitude(lat), longitude(lon) {}
};

struct Edge {
    string city1;
    string city2;
    double distance;

    Edge(string c1, string c2, double dist)
        : city1(c1), city2(c2), distance(dist) {}
};

double toRadians(double degrees) {
    return degrees * M_PI / 180;
}

double calcDistance(double lat1, double lon1, double lat2, double lon2) {
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    // Haversine formula
    double a = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return EARTH_RADIUS * c;
}

// Prim's algorithm to find Minimum Spanning Tree
vector<Edge> primMST(const vector<CityCoords>& cities) {
    int n = cities.size();
    vector<Edge> mst;

    if (n == 0) return mst;

    // Track which cities are in the MST
    vector<bool> inMST(n, false);

    // Track minimum distance to each city from the MST
    vector<double> minDist(n, numeric_limits<double>::infinity());

    // Track which city in MST connects to each city with minimum distance
    vector<int> parent(n, -1);

    // Start with city 0
    minDist[0] = 0;

    // Build MST with n-1 edges
    for (int i = 0; i < n; i++) {
        // Find the minimum distance city not yet in MST
        int minIndex = -1;
        double minValue = numeric_limits<double>::infinity();

        for (int j = 0; j < n; j++) {
            if (!inMST[j] && minDist[j] < minValue) {
                minValue = minDist[j];
                minIndex = j;
            }
        }

        // Add this city to MST
        inMST[minIndex] = true;

        // Add edge to MST (skip for first city)
        if (parent[minIndex] != -1) {
            mst.push_back(Edge(
                cities[parent[minIndex]].name,
                cities[minIndex].name,
                minDist[minIndex]
            ));
        }

        // Update distances to all other cities
        for (int j = 0; j < n; j++) {
            if (!inMST[j]) {
                double dist = calcDistance(
                    cities[minIndex].latitude, cities[minIndex].longitude,
                    cities[j].latitude, cities[j].longitude
                );

                if (dist < minDist[j]) {
                    minDist[j] = dist;
                    parent[j] = minIndex;
                }
            }
        }
    }

    return mst;
}

int main() {
    // The cities from the assignment
    vector<CityCoords> cityCoords = {
        CityCoords("Frankfurt", 50.1109, 8.6821),
        CityCoords("Copenhagen", 55.6761, 12.5683),
        CityCoords("Prague", 50.0755, 14.4378),
        CityCoords("Rome", 41.9028, 12.4964),
        CityCoords("Vienna", 48.2082, 16.3738),
        CityCoords("Budapest", 47.4979, 19.0402),
        CityCoords("Barcelona", 41.3784, 2.1915),
        CityCoords("Florence", 43.7696, 11.2558),
        CityCoords("Berlin", 52.52, 13.405),
        CityCoords("Amsterdam", 52.3676, 4.9041),
        CityCoords("Paris", 48.8566, 2.3522)
    };

    // Find the MST using Prim's algorithm
    vector<Edge> mst = primMST(cityCoords);

    // Print the results - one edge per line with city names and distances
    double totalDistance = 0.0;

    for (const auto& edge : mst) {
        cout << fixed << setprecision(2);
        cout << edge.city1 << " -- " << edge.city2
             << " : " << edge.distance << " km" << endl;
        totalDistance += edge.distance;
    }

    // Print the sum of distances
    cout << fixed << setprecision(2);
    cout << "\nTotal Distance: " << totalDistance << " km" << endl;

    return 0;
}
