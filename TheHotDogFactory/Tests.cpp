#include <iostream>
#include <cassert>
#include "heap.h"
#include "foodstuff.h"
#include "functors.h"

using std::cout;

// Simple integer comparator for testing
struct IntComparator {
    bool operator()(int a, int b) const {
        return a < b;
    }
};

void testBasicHeapOperations() {
    cout << "Testing basic heap operations with integers..." << "\n";

    Heap<int, IntComparator> heap;

    // Test empty
    assert(heap.empty());
    assert(heap.size() == 0);

    // Test add
    heap.add(5);
    heap.add(3);
    heap.add(7);
    heap.add(1);
    heap.add(9);

    assert(!heap.empty());
    assert(heap.size() == 5);

    // Test top (should be minimum)
    assert(heap.top() == 1);

    // Test remove (should extract in ascending order)
    assert(heap.remove() == 1);
    assert(heap.remove() == 3);
    assert(heap.remove() == 5);
    assert(heap.remove() == 7);
    assert(heap.remove() == 9);

    assert(heap.empty());

    cout << "  PASSED: Basic heap operations" << "\n";
}

void testFoodstuffHeap() {
    cout << "Testing heap with Foodstuff objects..." << "\n";

    Heap<Foodstuff, Cheapest> heap;

    // Create test foodstuffs with known cost/weight ratios
    Foodstuff cheap("Cheap Item", 10, 5);      // $0.50/lb
    Foodstuff medium("Medium Item", 10, 10);   // $1.00/lb
    Foodstuff expensive("Expensive Item", 10, 20); // $2.00/lb
    Foodstuff cheapest("Cheapest Item", 10, 1);    // $0.10/lb

    heap.add(medium);
    heap.add(expensive);
    heap.add(cheap);
    heap.add(cheapest);

    assert(heap.size() == 4);

    // Should extract in order of cost per pound (cheapest first)
    Foodstuff first = heap.remove();
    assert(first.name == "Cheapest Item");
    assert(first.getCostPerPound() == 0.10);

    Foodstuff second = heap.remove();
    assert(second.name == "Cheap Item");
    assert(second.getCostPerPound() == 0.50);

    Foodstuff third = heap.remove();
    assert(third.name == "Medium Item");
    assert(third.getCostPerPound() == 1.00);

    Foodstuff fourth = heap.remove();
    assert(fourth.name == "Expensive Item");
    assert(fourth.getCostPerPound() == 2.00);

    assert(heap.empty());

    cout << "  PASSED: Foodstuff heap operations" << "\n";
}

void testHeapWithDuplicates() {
    cout << "Testing heap with duplicate values..." << "\n";

    Heap<int, IntComparator> heap;

    heap.add(5);
    heap.add(3);
    heap.add(5);
    heap.add(3);
    heap.add(1);

    assert(heap.size() == 5);

    assert(heap.remove() == 1);
    assert(heap.remove() == 3);
    assert(heap.remove() == 3);
    assert(heap.remove() == 5);
    assert(heap.remove() == 5);

    cout << "  PASSED: Heap with duplicates" << "\n";
}

void testLargeHeap() {
    cout << "Testing heap with many elements..." << "\n";

    Heap<int, IntComparator> heap;

    // Insert 100 elements
    for (int i = 100; i > 0; i--) {
        heap.add(i);
    }

    assert(heap.size() == 100);

    // Extract all elements - should be in sorted order
    for (int i = 1; i <= 100; i++) {
        assert(heap.remove() == i);
    }

    assert(heap.empty());

    cout << "  PASSED: Large heap operations" << "\n";
}

void testHeapException() {
    cout << "Testing heap exception handling..." << "\n";

    Heap<int, IntComparator> heap;

    bool exceptionCaught = false;
    try {
        heap.remove();  // Should throw exception
    } catch (const std::runtime_error& e) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);

    exceptionCaught = false;
    try {
        heap.top();  // Should throw exception
    } catch (const std::runtime_error& e) {
        exceptionCaught = true;
    }

    assert(exceptionCaught);

    cout << "  PASSED: Exception handling" << "\n";
}

void testInstructorScenario() {
    cout << "Testing instructor's hot dog scenario..." << "\n";

    Rng rng(21324); // Use same seed as main program
    Heap<Foodstuff, Cheapest> h;

    // Simulate the instructor's logic
    int count = 0;
    for(int i = 0; i < 10; i++) {
        while(h.size() < 10) {
            Foodstuff ingredient = getRandomFoodstuff(rng);
            h.add(ingredient);
        }
        Foodstuff selected = h.remove();
        count++;
    }

    assert(count == 10);
    assert(h.size() == 9); // Should have 9 left after removing 10 from a heap that kept getting filled to 10

    cout << "  PASSED: Instructor scenario" << "\n";
}

int main() {
    cout << "========================================" << "\n";
    cout << "Running Heap Implementation Tests" << "\n";
    cout << "========================================" << "\n";
    cout << "\n";

    testBasicHeapOperations();
    testFoodstuffHeap();
    testHeapWithDuplicates();
    testLargeHeap();
    testHeapException();
    testInstructorScenario();

    cout << "\n";
    cout << "========================================" << "\n";
    cout << "All tests passed!" << "\n";
    cout << "========================================" << "\n";

    return 0;
}
