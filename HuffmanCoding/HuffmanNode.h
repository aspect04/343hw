#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

#include <memory>

struct HuffmanNode {
    char character;
    int frequency;
    int tiebreaker;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;

    HuffmanNode(char ch, int freq, int tie)
        : character(ch), frequency(freq), tiebreaker(tie), left(nullptr), right(nullptr) {}

    HuffmanNode(int freq, int tie, std::shared_ptr<HuffmanNode> l, std::shared_ptr<HuffmanNode> r)
        : character('\0'), frequency(freq), tiebreaker(tie), left(l), right(r) {}

    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

struct HuffmanNodeComparator {
    bool operator()(const std::shared_ptr<HuffmanNode>& a, const std::shared_ptr<HuffmanNode>& b) const {
        if (a->frequency != b->frequency) {
            return a->frequency > b->frequency;  // Min heap by frequency
        }
        return a->tiebreaker > b->tiebreaker;  // If tied, use insertion order (smaller tiebreaker first)
    }
};

#endif //HUFFMANNODE_H
