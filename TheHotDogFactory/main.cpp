#include <iostream>
#include <string>
#include <vector>
#include "rng.h"
#include "foodstuff.h"
#include "heap.h"
#include "functors.h"

using std::cout;
using std::string;
using std::vector;


void runTests() {
    // Test basic heap operations
    Heap<int, std::less<int>> intHeap;

    // Test add and size
    intHeap.add(5);
    intHeap.add(3);
    intHeap.add(7);
    intHeap.add(1);

    // Test that minimum is extracted first
    int min = intHeap.remove();
    if (min != 1) {
        cout << "ERROR: Expected 1, got " << min << "\n";
    }

    // Test with Foodstuff
    Heap<Foodstuff, Cheapest> foodHeap;
    foodHeap.add(Foodstuff("cheap", 10, 5));    // $0.50/lb
    foodHeap.add(Foodstuff("expensive", 10, 20)); // $2.00/lb
    foodHeap.add(Foodstuff("medium", 10, 10));   // $1.00/lb

    Foodstuff cheapest = foodHeap.remove();
    if (cheapest.name != "cheap") {
        cout << "ERROR: Expected 'cheap', got '" << cheapest.name << "'\n";
    }

    cout << "Tests completed successfully!\n\n";
}

void makeHotDogs() {
    Rng rng(21324); 

    Heap<Foodstuff, Cheapest> h;
    vector<Foodstuff> ingredients;

    for(int i = 0; i < 10; i++) {
        while(h.size() < 10) {
            Foodstuff ingredient = getRandomFoodstuff(rng);
            h.add(ingredient);
        }
        ingredients.push_back(h.remove());
    }

    int totalCost = 0;
    int totalWeight = 0;
    for(Foodstuff ingredient : ingredients) {
        printf("%-12s - cost: %3d  weight: %3d  CostPerPound: %3f\n", ingredient.name.c_str(), ingredient.cost, ingredient.weight, ingredient.getCostPerPound());
        totalCost += ingredient.cost;
        totalWeight += ingredient.weight;
    }
    cout << "total cost:   " << totalCost << "\n";
    cout << "total weight: " << totalWeight << "\n";
}


int main() {
    runTests();
    makeHotDogs();
    return 0;
}
