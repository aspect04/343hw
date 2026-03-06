#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <functional>
#include "Fruit.h"
#include "rng.h"

using namespace std;

class FruitFactory {
    using SpawnFn = function<Fruit*()>;
    vector<pair<int, SpawnFn>> entries;  // {weight, factory_function}
    int totalWeight = 0;
    Rng& rng;

public:
    FruitFactory(Rng& rng) : rng(rng) {
        // Higher weight = more common
        entries.push_back({35, []() -> Fruit* { return new Banana(); }});
        entries.push_back({25, []() -> Fruit* { return new Lemon(); }});
        entries.push_back({20, []() -> Fruit* { return new Avocado(); }});
        entries.push_back({15, []() -> Fruit* { return new Durian(); }});
        entries.push_back({5,  []() -> Fruit* { return new Watermelon(); }});

        for (auto& e : entries)
            totalWeight += e.first;
    }

    Fruit* spawn() {
        int roll = rng.randint(0, totalWeight - 1);
        int accumulated = 0;
        for (auto& e : entries) {
            accumulated += e.first;
            if (accumulated > roll)
                return e.second();
        }
        return entries.back().second(); // fallback (should never reach)
    }
};
#endif //FACTORY_H
