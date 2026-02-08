#include <iostream>
#include <vector>
#include <string>
#include "PathFinder.h"

using namespace std;

int main() {
    vector<string> map;
    string line;

    cout << "Enter the map (press Ctrl+D or Ctrl+Z when done):" << endl;

    // Read the map from standard input
    while (getline(cin, line)) {
        map.push_back(line);
    }

    if (map.empty()) {
        cout << "Error: No map provided!" << endl;
        return 1;
    }

    PathFinder pathfinder(map);
    int totalCost = 0;

    if (pathfinder.findPath(totalCost)) {
        cout << "\nTotal cost: " << totalCost << endl;
    } else {
        cout << "\nNo path exists from F to %!" << endl;
    }

    return 0;
}
