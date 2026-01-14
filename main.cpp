#include <iostream>
#include <string>
#include "CircularLinkedList.h"


int main() {
    CircularLinkedList<std::string> residents({"Laing", "Wilder",  "Frobisher"});
    int k = 1;
    while(residents.size() > 1) {
        std::string eaten = residents.removeNext(k);  // k == 1
        std::cout << "Eaten: " << eaten << "\n";
    }

    std::string winner = residents.getCurrent();
    std::cout << "The winner is " << winner << "!\n";    return 0;
}