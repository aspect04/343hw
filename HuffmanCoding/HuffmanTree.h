#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "BitSet.h"
#include "HuffmanNode.h"
#include <map>
#include <queue>
#include <vector>
#include <algorithm>

class HuffmanTree {
private:
    std::shared_ptr<HuffmanNode> root;
    std::map<char, BitSet> codes;
    std::map<char, BitSet> canonicalCodes;
    int nextTiebreaker;

    void generateCodes(std::shared_ptr<HuffmanNode> node, BitSet currentCode) {
        if (!node) return;

        if (node->isLeaf()) {
            codes[node->character] = currentCode;
        } else {
            BitSet leftCode = currentCode;
            leftCode.append(false);
            generateCodes(node->left, leftCode);

            BitSet rightCode = currentCode;
            rightCode.append(true);
            generateCodes(node->right, rightCode);
        }
    }

public:
    HuffmanTree() : root(nullptr), nextTiebreaker(0) {}

    // Step 1: Count character frequencies
    std::map<char, int> countFrequencies(const std::string& text) {
        std::map<char, int> frequencies;
        for (char c : text) {
            frequencies[c]++;
        }
        return frequencies;
    }

    // Step 2: Build Huffman tree
    void buildTree(const std::map<char, int>& frequencies) {
        std::priority_queue<std::shared_ptr<HuffmanNode>,
                          std::vector<std::shared_ptr<HuffmanNode>>,
                          HuffmanNodeComparator> pq;

        // Populate priority queue in map order (sorted by character)
        for (const auto& [ch, freq] : frequencies) {
            pq.push(std::make_shared<HuffmanNode>(ch, freq, nextTiebreaker++));
        }

        // Build tree
        while (pq.size() > 1) {
            auto left = pq.top();  // First dequeued is left child
            pq.pop();
            auto right = pq.top(); // Second dequeued is right child
            pq.pop();

            int combinedFreq = left->frequency + right->frequency;
            auto parent = std::make_shared<HuffmanNode>(combinedFreq, nextTiebreaker++, left, right);
            pq.push(parent);
        }

        root = pq.top();
    }

    // Step 3: Generate codes
    void generateCodes() {
        codes.clear();
        BitSet empty;
        generateCodes(root, empty);
    }

    // Step 4: Generate canonical codes
    void generateCanonicalCodes() {
        struct CodeInfo {
            char character;
            int numBits;
        };

        std::vector<CodeInfo> codeInfo;
        for (const auto& [ch, bitset] : codes) {
            codeInfo.push_back({ch, bitset.size()});
        }

        // Sort by length, then by character
        std::sort(codeInfo.begin(), codeInfo.end(), [](const CodeInfo& a, const CodeInfo& b) {
            if (a.numBits != b.numBits) {
                return a.numBits < b.numBits;
            }
            return a.character < b.character;
        });

        // Assign canonical codes
        canonicalCodes.clear();
        int currentCode = 0;
        int currentLength = 0;

        for (const auto& info : codeInfo) {
            if (info.numBits > currentLength) {
                currentCode <<= (info.numBits - currentLength);
                currentLength = info.numBits;
            }

            BitSet canonical;
            for (int i = currentLength - 1; i >= 0; i--) {
                canonical.append((currentCode >> i) & 1);
            }
            canonicalCodes[info.character] = canonical;
            currentCode++;
        }
    }

    // Step 5: Encode text
    BitSet encodeText(const std::string& text, bool useCanonical = false) {
        BitSet encoded;
        const auto& codesToUse = useCanonical ? canonicalCodes : codes;

        for (char c : text) {
            encoded.append(codesToUse.at(c));
        }
        return encoded;
    }

    const std::map<char, BitSet>& getCodes() const {
        return codes;
    }

    const std::map<char, BitSet>& getCanonicalCodes() const {
        return canonicalCodes;
    }
};

#endif //HUFFMANTREE_H
