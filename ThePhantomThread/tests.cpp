#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <iomanip>
#include <cassert>

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

void printMST(const vector<Edge>& mst) {
    cout << "Minimum Spanning Tree:" << endl;
    cout << "========================================" << endl;

    double totalDistance = 0;

    for (const auto& edge : mst) {
        cout << fixed << setprecision(2);
        cout << edge.city1 << " -- " << edge.city2
             << " : " << edge.distance << " km" << endl;
        totalDistance += edge.distance;
    }

    cout << "========================================" << endl;
    cout << "Total Distance: " << fixed << setprecision(2)
         << totalDistance << " km" << endl;
}

double getTotalDistance(const vector<Edge>& mst) {
    double total = 0;
    for (const auto& edge : mst) {
        total += edge.distance;
    }
    return total;
}

// Test case 1: Single city (edge case)
void testSingleCity() {
    cout << "\n=== Test 1: Single City (Edge Case) ===" << endl;

    vector<CityCoords> testCities = {
        CityCoords("Lonely", 50.0, 10.0)
    };

    vector<Edge> mst = primMST(testCities);

    // Should have 0 edges for 1 city
    assert(mst.size() == 0);
    assert(getTotalDistance(mst) == 0.0);

    cout << "✓ Test passed: Single city has 0 edges" << endl;
    cout << "  Expected: 0 edges, Got: " << mst.size() << " edges" << endl;
}

// Test case 2: Two cities
void testTwoCities() {
    cout << "\n=== Test 2: Two Cities ===" << endl;

    vector<CityCoords> testCities = {
        CityCoords("CityA", 0.0, 0.0),
        CityCoords("CityB", 1.0, 1.0)
    };

    vector<Edge> mst = primMST(testCities);

    // Should have 1 edge for 2 cities
    assert(mst.size() == 1);

    cout << "✓ Test passed: Two cities have 1 edge" << endl;
    cout << "  Expected: 1 edge, Got: " << mst.size() << " edge" << endl;
    printMST(mst);
}

// Test case 3: Simple triangle
void testSimpleTriangle() {
    cout << "\n=== Test 3: Triangle (3 Cities) ===" << endl;

    vector<CityCoords> testCities = {
        CityCoords("A", 0.0, 0.0),
        CityCoords("B", 0.0, 1.0),
        CityCoords("C", 1.0, 0.0)
    };

    vector<Edge> mst = primMST(testCities);

    // Should have 2 edges for 3 cities
    assert(mst.size() == 2);

    cout << "✓ Test passed: Triangle has 2 edges" << endl;
    cout << "  Expected: 2 edges, Got: " << mst.size() << " edges" << endl;
    printMST(mst);
}

// Test case 4: Four cities in a square
void testSquare() {
    cout << "\n=== Test 4: Square Configuration (4 Cities) ===" << endl;

    vector<CityCoords> testCities = {
        CityCoords("NW", 52.0, 0.0),
        CityCoords("NE", 52.0, 1.0),
        CityCoords("SW", 51.0, 0.0),
        CityCoords("SE", 51.0, 1.0)
    };

    vector<Edge> mst = primMST(testCities);

    // Should have 3 edges for 4 cities
    assert(mst.size() == 3);

    cout << "✓ Test passed: Square has 3 edges" << endl;
    cout << "  Expected: 3 edges, Got: " << mst.size() << " edges" << endl;
    printMST(mst);
}

// Test case 5: Line of cities
void testLinearCities() {
    cout << "\n=== Test 5: Linear Configuration (5 Cities) ===" << endl;

    // Five cities in a line along the equator
    vector<CityCoords> testCities = {
        CityCoords("City1", 0.0, 0.0),
        CityCoords("City2", 0.0, 1.0),
        CityCoords("City3", 0.0, 2.0),
        CityCoords("City4", 0.0, 3.0),
        CityCoords("City5", 0.0, 4.0)
    };

    vector<Edge> mst = primMST(testCities);

    // Should have 4 edges for 5 cities
    assert(mst.size() == 4);

    cout << "✓ Test passed: Linear configuration has 4 edges" << endl;
    cout << "  Expected: 4 edges, Got: " << mst.size() << " edges" << endl;
    printMST(mst);
}

// Test case 6: Known European cities subset
void testRealCitiesSubset() {
    cout << "\n=== Test 6: Real European Cities Subset ===" << endl;

    // A small subset of real European cities to verify distances
    vector<CityCoords> testCities = {
        CityCoords("Paris", 48.8566, 2.3522),
        CityCoords("Berlin", 52.52, 13.405),
        CityCoords("Rome", 41.9028, 12.4964)
    };

    vector<Edge> mst = primMST(testCities);

    // Should have 2 edges for 3 cities
    assert(mst.size() == 2);

    cout << "✓ Test passed: 3 real cities have 2 edges" << endl;
    cout << "  Expected: 2 edges, Got: " << mst.size() << " edges" << endl;
    printMST(mst);

    // Verify distances are reasonable (Paris-Berlin ~878km, Paris-Rome ~1105km, Berlin-Rome ~1184km)
    // MST should connect Paris-Berlin and Berlin-Rome (or Paris-Rome and one other)
    double total = getTotalDistance(mst);
    cout << "  Total MST distance: " << fixed << setprecision(2) << total << " km" << endl;

    // The minimum should be less than the sum of all edges
    // Paris-Berlin + Berlin-Rome should be around 2062km
    assert(total > 1500 && total < 2500);
    cout << "  Distance check passed (reasonable range)" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  PRIM'S MST ALGORITHM - TEST SUITE" << endl;
    cout << "========================================" << endl;

    int totalTests = 6;
    int passedTests = 0;

    try {
        testSingleCity();
        passedTests++;
    } catch (const exception& e) {
        cout << "✗ Test 1 FAILED: " << e.what() << endl;
    }

    try {
        testTwoCities();
        passedTests++;
    } catch (const exception& e) {
        cout << "✗ Test 2 FAILED: " << e.what() << endl;
    }

    try {
        testSimpleTriangle();
        passedTests++;
    } catch (const exception& e) {
        cout << "✗ Test 3 FAILED: " << e.what() << endl;
    }

    try {
        testSquare();
        passedTests++;
    } catch (const exception& e) {
        cout << "✗ Test 4 FAILED: " << e.what() << endl;
    }

    try {
        testLinearCities();
        passedTests++;
    } catch (const exception& e) {
        cout << "✗ Test 5 FAILED: " << e.what() << endl;
    }

    try {
        testRealCitiesSubset();
        passedTests++;
    } catch (const exception& e) {
        cout << "✗ Test 6 FAILED: " << e.what() << endl;
    }

    cout << "\n========================================" << endl;
    cout << "  TEST RESULTS" << endl;
    cout << "========================================" << endl;
    cout << "Passed: " << passedTests << "/" << totalTests << " tests" << endl;

    if (passedTests == totalTests) {
        cout << "\n✓ ALL TESTS PASSED! Algorithm is working correctly." << endl;
        cout << "Ready to discover the Phantom Thread!" << endl;
        return 0;
    } else {
        cout << "\n✗ SOME TESTS FAILED! Please review the implementation." << endl;
        return 1;
    }
}
