#include <iostream>
#include <map>
#include <iomanip>
#include "rng.h"
#include "Fruit.h"
#include "Factory.h"

using namespace std;


//  PROPORTIONS TEST
void runProportionTest(int seed, int trials = 10000) {
    cout << "\n=== SPAWN PROPORTION TEST (" << trials << " trials, seed=" << seed << ") ===\n";
    Rng testRng(seed);
    FruitFactory factory(testRng);

    map<string, int> counts;
    for (int i = 0; i < trials; i++) {
        Fruit* f = factory.spawn();
        counts[f->getName()]++;
        delete f;
    }

    cout << left << setw(14) << "Fruit"
         << setw(10) << "Count"
         << setw(10) << "Actual%"
         << "Expected%\n";
    cout << string(44, '-') << "\n";

    map<string, int> expected = {
        {"Banana", 35}, {"Lemon", 25}, {"Avocado", 20}, {"Durian", 15}, {"Watermelon", 5}
    };
    for (auto& entry : counts) {
        double actual = 100.0 * entry.second / trials;
        cout << left << setw(14) << entry.first
             << setw(10) << entry.second
             << setw(10) << fixed << setprecision(1) << actual
             << expected[entry.first] << "%\n";
    }
    cout << "\n";
}

//  GAME LOOP
void runGame() {
    Rng rng;
    FruitFactory factory(rng);

    int playerHP = 100;
    int fruitsDefeated = 0;

    cout << R"(
 _____ _____  _   _ ___ _____   _    ____   ___   ____    _    _     _   _ ____  _____
|  ___|  _ \| | | |_ _|_   _| / \  |  _ \ / _ \ / ___|  / \  | |   | \ | |  _ \| ____|
| |_  | |_) | | | || |  | |  / _ \ | |_) | | | | |     / _ \ | |   |  \| | |_) |  _|
|  _| |  _ <| |_| || |  | | / ___ \|  __/| |_| | |___ / ___ \| |___| |\  |  __/| |___
|_|   |_| \_\\___/|___| |_|/_/   \_\_|    \___/ \____/_/   \_\_____|_| \_|_|   |_____|

    THE NIGHTMARE PRODUCE APOCALYPSE
)" << "\n";

    cout << "Year 2047. A cosmic event has awakened Earth's fruits and vegetables.\n";
    cout << "They are NOT happy. You are NOT safe. Your HP: " << playerHP << "\n\n";

    while (playerHP > 0) {
        cout << "--- You trudge through the wasteland... ---\n";
        cout << "[Press ENTER to encounter a fruit, or type 'q' to surrender]\n> ";

        string input;
        getline(cin, input);
        if (input == "q") {
            cout << "\nYou flee screaming into the horizon. Coward. You lasted "
                 << fruitsDefeated << " fight(s).\n";
            return;
        }

        Fruit* enemy = factory.spawn();
        cout << "\n*** A wild " << enemy->getName() << " descends from the sky! ***\n\n";

        // Combat loop
        while (enemy->isLiving() && playerHP > 0) {
            cout << "[ATTACK] Press ENTER to swing your trusty spatula, or 'q' to flee\n> ";
            getline(cin, input);

            if (input == "q") {
                cout << "You run. The " << enemy->getName() << " shrieks victoriously.\n\n";
                delete enemy;
                goto next_encounter;
            }

            // Player attacks (8-20 damage)
            int playerDmg = rng.randint(8, 20);
            cout << "You whack the " << enemy->getName() << " for " << playerDmg << " damage!\n";
            cout << enemy->takeDamage(playerDmg) << "\n";

            if (!enemy->isLiving()) break;

            // Enemy attacks
            cout << enemy->getAttackMessage() << "\n";
            int enemyDmg = enemy->getAttackDamage();
            playerHP -= enemyDmg;
            cout << "You take " << enemyDmg << " damage! Your HP: " << max(0, playerHP) << "\n\n";
        }

        if (!enemy->isLiving()) {
            fruitsDefeated++;
            cout << "\n[VICTORY] The " << enemy->getName()
                 << " has been neutralized. Fruits defeated: " << fruitsDefeated << "\n";
            cout << "Your HP: " << playerHP << "\n\n";
        }

        delete enemy;
        next_encounter:;
    }

    cout << "\n=== GAME OVER ===\n";
    cout << "The produce has won. You survived " << fruitsDefeated << " encounter(s) before falling.\n";
    cout << "The Watermelon overlords send their regards.\n";
}


int main() {

    runProportionTest(42);
    runGame();

    return 0;
}