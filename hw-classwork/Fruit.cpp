#include <vector>
#include <iostream>
using namespace std;


class Fruit {
public:
    virtual void eatMe() { cout << "yum!\n"; }
};
class Apple : public Fruit {
public:
    void eatMe() { cout << "Le apple! \n"; }
};
class Banana : public Fruit {
public:
    void eatMe() { cout << "Baananana!\n";}
};

int main() {
    vector<Fruit*> fruits;
    fruits.push_back(new Apple());
    fruits.push_back(new Banana());
    fruits.push_back(new Apple());
    for (Fruit* f:fruits) {
        f->eatMe();
    }
    return 0;

}