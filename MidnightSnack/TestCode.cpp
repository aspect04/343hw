#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "PathFinder.h"

using namespace std;

void runTest(const string& testName, const vector<string>& map, bool shouldFindPath, int expectedCost = -1) {
    cout << "\n========================================" << endl;
    cout << "Test: " << testName << endl;
    cout << "========================================" << endl;

    cout << "Original Map:" << endl;
    for (const string& line : map) {
        cout << line << endl;
    }
    cout << endl;

    PathFinder pathfinder(map);
    int totalCost = 0;

    bool foundPath = pathfinder.findPath(totalCost);

    if (shouldFindPath) {
        assert(foundPath && "Expected to find a path but didn't!");
        cout << "\nTotal cost: " << totalCost << endl;

        if (expectedCost != -1) {
            assert(totalCost == expectedCost && "Cost doesn't match expected value!");
            cout << "Cost matches expected value!" << endl;
        }

        cout << "TEST PASSED!" << endl;
    } else {
        assert(!foundPath && "Expected no path but found one!");
        cout << "\nNo path exists from F to %!" << endl;
        cout << "TEST PASSED!" << endl;
    }
}

int main() {
    cout << "Running Midnight Snack Pathfinding Tests..." << endl;
    cout << "============================================" << endl;

    // Test 1: Original problem map
    vector<string> test1 = {
        "###############################",
        "#F    YYYY      ##  ##  ###   #",
        "# ##  ####   #####  ##  ##    #",
        "# ##  ####   #####            #",
        "# ##  ####   #####  ###  #### #",
        "#        YYYY       ###  #### #",
        "# #######YYYY#####  ###YY#### #",
        "# #######YYYY#####  ###YY#### #",
        "# ##         #####     YY     #",
        "#            #####  ######    #",
        "# ####              ##% ##    #",
        "# ####YYY###  ####  ##  ##  ###",
        "#     YYY###        ##        #",
        "###############################"
    };
    runTest("Original Problem Map", test1, true);

    // Test 2: Simple straight path
    vector<string> test2 = {
        "#####",
        "#F  #",
        "#   #",
        "#  %#",
        "#####"
    };
    runTest("Simple Straight Path", test2, true, 4);

    // Test 3: No path exists (completely blocked)
    vector<string> test3 = {
        "#######",
        "#F    #",
        "#######",
        "#    %#",
        "#######"
    };
    runTest("No Path Exists", test3, false);

    // Test 4: Path with Agent Yellow (high cost)
    vector<string> test4 = {
        "#########",
        "#F      #",
        "# ####  #",
        "# #YYYY #",
        "# #Y%YY #",
        "# #YYYY #",
        "# ####  #",
        "#       #",
        "#########"
    };
    runTest("Path Through Agent Yellow", test4, true);

    // Test 5: Choose cheaper path (avoid Yellow)
    vector<string> test5 = {
        "###########",
        "#F        #",
        "# ####### #",
        "# #YYYYY# #",
        "# #YYYYY# #",
        "# #YYYYY# #",
        "# ####### #",
        "#        %#",
        "###########"
    };
    runTest("Avoid Expensive Yellow Path", test5, true, 14);

    // Test 6: Diagonal barrier (no diagonal movement)
    vector<string> test6 = {
        "#####",
        "#F #%",
        "## ##",
        "#   #",
        "#####"
    };
    runTest("No Path - Diagonal Barrier", test6, false);

    // Test 7: Adjacent start and goal
    vector<string> test7 = {
        "####",
        "#F%#",
        "####"
    };
    runTest("Adjacent Start and Goal", test7, true, 1);

    // Test 8: Yellow vs regular path choice
    vector<string> test8 = {
        "###########",
        "#F        #",
        "#Y#########",
        "#Y       %#",
        "###########"
    };
    runTest("Yellow vs Longer Regular Path", test8, true);

    // Test 9: Spiral path
    vector<string> test9 = {
        "###########",
        "#F###    ##",
        "# ### ## ##",
        "# ### ## ##",
        "#     #% ##",
        "####### ###",
        "###########"
    };
    runTest("Spiral/Maze Path", test9, true);

    // Test 10: All Yellow path (no choice)
    vector<string> test10 = {
        "#####",
        "#FYY#",
        "##Y##",
        "##Y%#",
        "#####"
    };
    runTest("Only Yellow Path Available", test10, true, 13);

    cout << "\n========================================" << endl;
    cout << "All tests passed successfully!" << endl;
    cout << "========================================" << endl;

    return 0;
}
