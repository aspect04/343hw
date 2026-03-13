#include <iostream>
#include <vector>
#include <string>
#include "PathFinder.h"

using namespace std;

// Forward declaration of tests
int runMidnightSnackTests();

int main() {
    vector<string> map;
    string line;

    cout << "Enter the map (press Ctrl+D or Ctrl+Z when done, or enter empty line to run default tests):" << endl;

    // Read the map from standard input
    while (getline(cin, line) && !line.empty()) {
        map.push_back(line);
    }

    if (!map.empty()) {
        PathFinder pathfinder(map);
        int totalCost = 0;

        if (pathfinder.findPath(totalCost)) {
            cout << "\nTotal cost: " << totalCost << endl;
        } else {
            cout << "\nNo path exists from F to %!" << endl;
        }
        cout << "\n" << endl;
    } else {
        cout << "No map provided, proceeding to tests..." << endl;
    }

    cout << "--- Running Test Cases ---" << endl;
    runMidnightSnackTests();

    return 0;
}