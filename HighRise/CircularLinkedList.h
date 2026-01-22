#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H
#include <string>
#include <stdexcept>


template <typename T>
class CircularLinkedList {
    public:
    CircularLinkedList() : head_(nullptr), tail_(nullptr), current_(nullptr), size_(0) {}

    CircularLinkedList(std::initializer_list<T> list) : head_(nullptr), tail_(nullptr), size_(0) {
        for (const T& item : list) {
            Node* newNode = new Node(item);

            if (head_ == nullptr) {
                head_ = newNode;
                newNode->next = head_; // Point to itself initially
            } else {
                tail_->next = newNode;
                newNode->next = head_; // Close the loop
            }
            tail_ = newNode;
            size_++;
        }
        current_ = head_; // Initialize current to head
    }
        ~CircularLinkedList() {
            if (!head_) return;
            Node* current = head_;
            for (size_t i = 0; i < size_; ++i) {
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        T removeNext(int k) {
            if (head_ == nullptr) {
                throw std::runtime_error("Cannot remove from empty list");
            }

            // Special case: only one node left
            if (size_ == 1) {
                T value = head_->value;
                delete head_;
                head_ = nullptr;
                tail_ = nullptr;
                current_ = nullptr;
                size_ = 0;
                return value;
            }

            // Find the node k steps ahead from current_
            Node* toRemove = current_;
            for (int i = 0; i < k; ++i) {
                toRemove = toRemove->next;
            }

            // Find the node before toRemove to update its next pointer
            Node* prev = current_;
            while (prev->next != toRemove) {
                prev = prev->next;
            }

            // Save the value
            T value = toRemove->value;

            // Update pointers to remove the node
            prev->next = toRemove->next;

            // Update head_ and tail_ if necessary
            if (toRemove == head_) {
                head_ = toRemove->next;
            }
            if (toRemove == tail_) {
                tail_ = prev;
            }

            // Update current_ to the next node after the removed one
            current_ = toRemove->next;

            // Delete the node
            delete toRemove;
            size_--;

            return value;
        }

        T getCurrent() {
            if (current_ == nullptr) {
                throw std::runtime_error("Cannot get current from empty list");
            }
            return current_->value;
        }
        size_t size() {
            return size_;
        }

    private:
    struct Node {
        Node(const T& val) : next(nullptr), prev(nullptr), value(val) {}

        Node* next;
        Node* prev;

        T value;
    };

        Node* current_;
        Node* head_ = nullptr;
        Node* tail_ = nullptr;
        size_t size_ = 0;


};



#endif //CIRCULARLINKEDLIST_H