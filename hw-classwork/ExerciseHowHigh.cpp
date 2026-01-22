#include <iostream>
#include <string>
using namespace std;

class Node {
    public:
        std::string value;
        Node* left;
        Node* right;
        Node(std::string value) : value(value), left(nullptr), right(nullptr) {};
};


void printTreeWithHeights(Node* node, int height = 0) {
    if (node == nullptr) {
        return;
    }

    // Print current node's value and height
    cout << "Value: " << node->value << ", Height: " << height << endl;

    // Recursively traverse left and right subtrees
    printTreeWithHeights(node->left, height + 1);
    printTreeWithHeights(node->right, height + 1);
}


int main() {

    Node* root = new Node("A");
    root->left = new Node("B");
    root->right = new Node("C");
    root->left->left = new Node("D");
    root->left->right = new Node("E");
    root->right->right = new Node("F");

    cout << "Tree nodes with their heights:" << endl;
    printTreeWithHeights(root);

    return 0;
}



