#pragma once
#include <vector>
#include <stdexcept>

using std::vector;

template<typename T, typename Comparator>
class Heap {
private:
    vector<T> data;
    Comparator comp;

    // Get parent index
    size_t parent(size_t i) const {
        return (i - 1) / 2;
    }

    // Get left child index
    size_t leftChild(size_t i) const {
        return 2 * i + 1;
    }

    // Get right child index
    size_t rightChild(size_t i) const {
        return 2 * i + 2;
    }

    // Swap two elements
    void swap(size_t i, size_t j) {
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    // Heapify up (bubble up)
    void heapifyUp(size_t i) {
        while (i > 0 && comp(data[i], data[parent(i)])) {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    // Heapify down (bubble down)
    void heapifyDown(size_t i) {
        size_t smallest = i;
        size_t left = leftChild(i);
        size_t right = rightChild(i);

        if (left < data.size() && comp(data[left], data[smallest])) {
            smallest = left;
        }

        if (right < data.size() && comp(data[right], data[smallest])) {
            smallest = right;
        }

        if (smallest != i) {
            swap(i, smallest);
            heapifyDown(smallest);
        }
    }

public:
    // Constructor
    Heap() : comp(Comparator()) {}

    // Insert element into heap (required method name: add)
    void add(const T& value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    // Remove and return the minimum element (required method name: remove)
    T remove() {
        if (empty()) {
            throw std::runtime_error("Heap is empty");
        }

        T minValue = data[0];
        data[0] = data.back();
        data.pop_back();

        if (!empty()) {
            heapifyDown(0);
        }

        return minValue;
    }

    // Get the minimum element without removing it
    const T& top() const {
        if (empty()) {
            throw std::runtime_error("Heap is empty");
        }
        return data[0];
    }

    // Check if heap is empty
    bool empty() const {
        return data.empty();
    }

    // Get size of heap
    size_t size() const {
        return data.size();
    }
};
