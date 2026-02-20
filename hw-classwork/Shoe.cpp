#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class Shoe {
private:
    double size;
    string color;
    string type;
public:
    Shoe(double size, string color, string type)
      : size(size), color(color), type(type) {;}

    double getSize() const { return size; }
    string getColor() const { return color; }
    string getType() const { return type; }

    //output
    friend std::ostream& operator<<(ostream& os, const Shoe& shoe) {
        os << "Shoe: " << shoe.color << ", " << shoe.size << ", " << shoe.type << "\n";
        return os;
    }
    //equality
    bool operator==(const Shoe& other) const {
        return size == other.size &&
               color == other.color &&
               type == other.type;
    }
};

namespace std {
    template<>
    struct hash<Shoe> {
        size_t operator()(const Shoe& shoe) const {
            size_t h1 = hash<double>{}(shoe.getSize());
            size_t h2 = hash<string>{}(shoe.getColor());
            size_t h3 = hash<string>{}(shoe.getType());

            // Combine the hashes (XOR and bit shifting)
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}

int main() {
    std::unordered_set<Shoe> shoes;

    Shoe shoe1(9.5, "black", "sneaker");
    Shoe shoe2(8.0, "red", "heel");
    Shoe shoe3(10.0, "brown", "boot");
    Shoe shoe4(9.5, "black", "sneaker");  // shoe1 dupe
    Shoe shoe5(7.5, "white", "sandal");
    Shoe shoe6(8.0, "red", "heel");       // shoe2 dupe
    Shoe shoe7(11.0, "blue", "loafer");
    Shoe shoe8(10.0, "brown", "boot");    // shoe3 dupe

    shoes.insert(shoe1);
    shoes.insert(shoe2);
    shoes.insert(shoe3);
    shoes.insert(shoe4);
    shoes.insert(shoe5);
    shoes.insert(shoe6);
    shoes.insert(shoe7);
    shoes.insert(shoe8);


    for (const auto& shoe : shoes) {
        cout  << shoe;
    }
    return 0;
}
