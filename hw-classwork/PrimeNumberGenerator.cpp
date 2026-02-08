#include <iostream>
#include <vector>

using namespace std;

static vector<int> primes;

// returns next prime number in vector primes
// starting at 2 or last number in given vector
int getNextPrime() {
    if (primes.empty()) return 2;
    else {
        int i = primes.back() + 1;
        while (true) {
            for (int j = 0; j < primes.size(); j++) {
                if (j == primes.size() - 1 && i % primes[j] != 0) return i;
                else if (i % primes[j] == 0) break;

            }
            i++;
        }
    }
}

int main() {

    for(int i = 0; i < 10; i++) {
        primes.push_back(getNextPrime());
    }
    for(int i = 0; i < 10; i++) {
        cout << primes[i] << endl;
    }


    return 0;
}