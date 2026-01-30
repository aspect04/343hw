#pragma once
#include "foodstuff.h"

// Comparator functor for Foodstuff objects
// Compares based on cost per pound (lower is better for hot dogs)
struct Cheapest {
    // Returns true if a has lower cost per pound than b (min-heap)
    bool operator()(const Foodstuff& a, const Foodstuff& b) const {
        return a.getCostPerPound() < b.getCostPerPound();
    }
};
