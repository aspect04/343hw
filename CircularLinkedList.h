#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H
#include "string"


template <typename T>
class CircularLinkedList {
    public:
        void removeNext();
        int size();
    private:
        Node current_;
        Node head_;
        Node tail_;

    class Node {
    public:
        std::string value;
        Node* pLeft;
        Node* pRight;
    };
};

#endif //CIRCULARLINKEDLIST_H
