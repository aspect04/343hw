#include "circularlinkedlist.h"
#include <iostream>
#include <cassert>

using namespace std;

// Helper function to print test header
void printTestHeader(const string& testName) {
    cout << "\n========================================\n";
    cout << "TEST: " << testName << "\n";
    cout << "========================================\n";
}

// Test 1: Basic example from the problem (k = 1)
void testBasicExample() {
    printTestHeader("Basic Example (k=1, 3 residents)");

    CircularLinkedList<string> residents({"Laing", "Wilder", "Frobisher"});

    cout << "Initial size: " << residents.size() << "\n";

    while(residents.size() > 1) {
        string eaten = residents.removeNext(1);
        cout << "Eaten: " << eaten << "\n";
    }

    string winner = residents.getCurrent();
    cout << "The winner is " << winner << "!\n";
    cout << "Expected: Frobisher\n";
    assert(winner == "Frobisher");
    cout << "✓ Test passed!\n";
}

// Test 2: k = 0 (removes current position)
void testKEqualsZero() {
    printTestHeader("k=0 (removes current position)");

    CircularLinkedList<string> list({"A", "B", "C", "D"});

    cout << "Initial: A, B, C, D\n";
    cout << "Current: " << list.getCurrent() << "\n";

    string removed = list.removeNext(0);
    cout << "Removed with k=0: " << removed << "\n";
    cout << "Expected: A\n";
    assert(removed == "A");

    cout << "New current: " << list.getCurrent() << "\n";
    cout << "Expected: B\n";
    assert(list.getCurrent() == "B");
    cout << "✓ Test passed!\n";
}

// Test 3: k > size (wraps around multiple times)
void testKGreaterThanSize() {
    printTestHeader("k > size (k=7 with 3 elements)");

    CircularLinkedList<string> list({"X", "Y", "Z"});

    cout << "Initial: X, Y, Z (size=3)\n";
    cout << "Current: " << list.getCurrent() << "\n";
    cout << "Removing with k=7 (wraps around: 7 % 3 = effective k of 1)\n";

    // Starting at X, move 7 steps: X->Y->Z->X->Y->Z->X->Y
    string removed = list.removeNext(7);
    cout << "Removed: " << removed << "\n";
    cout << "Expected: Y\n";
    assert(removed == "Y");
    cout << "✓ Test passed!\n";
}

// Test 4: Single element list
void testSingleElement() {
    printTestHeader("Single Element List");

    CircularLinkedList<int> list({42});

    cout << "Initial size: " << list.size() << "\n";
    cout << "Current: " << list.getCurrent() << "\n";
    assert(list.getCurrent() == 42);

    int removed = list.removeNext(0);
    cout << "Removed: " << removed << "\n";
    cout << "Size after removal: " << list.size() << "\n";
    assert(removed == 42);
    assert(list.size() == 0);
    cout << "✓ Test passed!\n";
}

// Test 5: Two element list with k = 1
void testTwoElements() {
    printTestHeader("Two Element List (k=1)");

    CircularLinkedList<string> list({"First", "Second"});

    cout << "Initial: First, Second\n";
    cout << "Current: " << list.getCurrent() << "\n";

    string removed = list.removeNext(1);
    cout << "Removed: " << removed << "\n";
    cout << "Expected: Second\n";
    assert(removed == "Second");

    cout << "Winner: " << list.getCurrent() << "\n";
    cout << "Expected: First\n";
    assert(list.getCurrent() == "First");
    cout << "✓ Test passed!\n";
}

// Test 6: Large k value
void testLargeK() {
    printTestHeader("Large k value (k=100 with 5 elements)");

    CircularLinkedList<int> list({1, 2, 3, 4, 5});

    cout << "Initial: 1, 2, 3, 4, 5\n";
    cout << "Current: " << list.getCurrent() << "\n";
    cout << "Removing with k=100\n";

    // Starting at 1, move 100 steps (100 % 5 = 0, so same as k=0)
    int removed = list.removeNext(100);
    cout << "Removed: " << removed << "\n";
    cout << "Expected: 1\n";
    assert(removed == 1);
    cout << "✓ Test passed!\n";
}

// Test 7: Classic Josephus Problem (k=2, n=7)
void testClassicJosephus() {
    printTestHeader("Classic Josephus (k=2, n=7)");

    CircularLinkedList<int> list({1, 2, 3, 4, 5, 6, 7});

    cout << "People: 1, 2, 3, 4, 5, 6, 7\n";
    cout << "Every 2nd person is eliminated:\n";

    while(list.size() > 1) {
        int eliminated = list.removeNext(2);
        cout << "Eliminated: " << eliminated << "\n";
    }

    int survivor = list.getCurrent();
    cout << "Survivor: " << survivor << "\n";
    cout << "Expected: 4\n";
    assert(survivor == 4);
    cout << "✓ Test passed!\n";
}

// Test 8: All elements removed one by one (k=1)
void testRemoveAll() {
    printTestHeader("Remove All Elements (k=1)");

    CircularLinkedList<char> list({'A', 'B', 'C', 'D', 'E'});

    cout << "Initial: A, B, C, D, E\n";
    int initialSize = list.size();
    cout << "Initial size: " << initialSize << "\n";

    while(list.size() > 1) {
        char removed = list.removeNext(1);
        cout << "Removed: " << removed << ", Size: " << list.size() << "\n";
    }

    char last = list.getCurrent();
    cout << "Last remaining: " << last << "\n";
    assert(list.size() == 1);
    cout << "✓ Test passed!\n";
}

// Test 9: k = size (wraps around exactly once)
void testKEqualsSize() {
    printTestHeader("k equals size (k=4 with 4 elements)");

    CircularLinkedList<string> list({"Alpha", "Beta", "Gamma", "Delta"});

    cout << "Initial: Alpha, Beta, Gamma, Delta\n";
    cout << "Current: " << list.getCurrent() << "\n";
    cout << "Removing with k=4 (same as k=0, wraps exactly once)\n";

    string removed = list.removeNext(4);
    cout << "Removed: " << removed << "\n";
    cout << "Expected: Alpha\n";
    assert(removed == "Alpha");
    cout << "✓ Test passed!\n";
}

// Test 10: Multiple rounds with different k values
void testMultipleRounds() {
    printTestHeader("Multiple Rounds with Varying k");

    CircularLinkedList<int> list({10, 20, 30, 40, 50});

    cout << "Initial: 10, 20, 30, 40, 50\n";

    cout << "Round 1: k=1\n";
    int r1 = list.removeNext(1);
    cout << "Removed: " << r1 << ", Current: " << list.getCurrent() << "\n";

    cout << "Round 2: k=2\n";
    int r2 = list.removeNext(2);
    cout << "Removed: " << r2 << ", Current: " << list.getCurrent() << "\n";

    cout << "Round 3: k=3\n";
    int r3 = list.removeNext(3);
    cout << "Removed: " << r3 << ", Current: " << list.getCurrent() << "\n";

    cout << "Remaining size: " << list.size() << "\n";
    assert(list.size() == 2);
    cout << "✓ Test passed!\n";
}

// Test 11: Very large k (k >> size)
void testVeryLargeK() {
    printTestHeader("Very Large k (k=1000 with 3 elements)");

    CircularLinkedList<string> list({"One", "Two", "Three"});

    cout << "Initial: One, Two, Three\n";
    cout << "Removing with k=1000\n";
    cout << "1000 % 3 = 1, so effectively k=1\n";

    string removed = list.removeNext(1000);
    cout << "Removed: " << removed << "\n";
    cout << "Expected: Two\n";
    assert(removed == "Two");
    cout << "✓ Test passed!\n";
}

// Test 12: Integer list with k = 3
void testIntegerList() {
    printTestHeader("Integer List (k=3)");

    CircularLinkedList<int> nums({100, 200, 300, 400, 500, 600});

    cout << "Initial: 100, 200, 300, 400, 500, 600\n";
    cout << "Eliminating with k=3:\n";

    while(nums.size() > 1) {
        int eliminated = nums.removeNext(3);
        cout << "Eliminated: " << eliminated << ", Remaining: " << nums.size() << "\n";
    }

    cout << "Winner: " << nums.getCurrent() << "\n";
    assert(nums.size() == 1);
    cout << "✓ Test passed!\n";
}

// Test 13: Edge case - k = size - 1
void testKSizeMinusOne() {
    printTestHeader("k = size - 1");

    CircularLinkedList<char> list({'W', 'X', 'Y', 'Z'});

    cout << "Initial: W, X, Y, Z (size=4)\n";
    cout << "Current: " << list.getCurrent() << "\n";
    cout << "Removing with k=3 (size-1)\n";

    // Starting at W, move 3 steps: W->X->Y->Z
    char removed = list.removeNext(3);
    cout << "Removed: " << removed << "\n";
    cout << "Expected: Z\n";
    assert(removed == 'Z');
    cout << "✓ Test passed!\n";
}

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║  CIRCULAR LINKED LIST TEST SUITE      ║\n";
    cout << "╚════════════════════════════════════════╝\n";

    try {
        testBasicExample();
        testKEqualsZero();
        testKGreaterThanSize();
        testSingleElement();
        testTwoElements();
        testLargeK();
        testClassicJosephus();
        testRemoveAll();
        testKEqualsSize();
        testMultipleRounds();
        testVeryLargeK();
        testIntegerList();
        testKSizeMinusOne();

        cout << "\n";
        cout << "╔════════════════════════════════════════╗\n";
        cout << "║  ALL TESTS PASSED SUCCESSFULLY! ✓     ║\n";
        cout << "╚════════════════════════════════════════╝\n";
        cout << "\n";

    } catch (const exception& e) {
        cout << "\n✗ TEST FAILED: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
