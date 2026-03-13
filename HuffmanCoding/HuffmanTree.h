#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "BitSet.h"
#include "HuffmanNode.h"
#include "Frequency.h"
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
        return ::countFrequencies(text);
    }

    // Step 2: Build Huffman tree
    void buildTree(const std::map<char, int>& frequencies) {
        root = nullptr;
        codes.clear();
        canonicalCodes.clear();
        nextTiebreaker = 0;

        if (frequencies.empty()) return;

        std::priority_queue<std::shared_ptr<HuffmanNode>,
                          std::vector<std::shared_ptr<HuffmanNode>>,
                          HuffmanNodeComparator> pq;

        // Populate priority queue in map order (sorted by character)
        for (const auto& pair : frequencies) {
            char ch = pair.first;
            int freq = pair.second;
            pq.push(std::make_shared<HuffmanNode>(ch, freq, nextTiebreaker++));
        }

        // Handle single character case
        if (pq.size() == 1) {
            auto lone = pq.top();
            pq.pop();
            // Create a dummy parent so the character has at least one bit (0)
            root = std::make_shared<HuffmanNode>(lone->frequency, nextTiebreaker++, lone, nullptr);
            return;
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
        if (!root) return;
        BitSet empty;
        generateCodes(root, empty);
    }

    // Step 4: Generate canonical codes
    void generateCanonicalCodes() {
        if (codes.empty()) return;
        struct CodeInfo {
            char character;
            int numBits;
        };

        std::vector<CodeInfo> codeInfo;
        for (const auto& pair : codes) {
            char ch = pair.first;
            const BitSet& bitset = pair.second;
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
        if (codesToUse.empty() && !text.empty()) return encoded; // Should not happen if tree built

        for (char c : text) {
            encoded.append(codesToUse.at(c));
        }
        return encoded;
    }

    // Step 6: Decode text (Round-trip)
    std::string decodeText(const BitSet& encoded, bool useCanonical = false) {
        if (!root || encoded.size() == 0) return "";

        std::string decoded = "";
        
        if (useCanonical) {
            // To decode canonical, we map bitsets back to characters
            std::map<std::string, char> reverseMap;
            for (const auto& pair : canonicalCodes) {
                reverseMap[pair.second.toBinaryString()] = pair.first;
            }

            std::string currentBits = "";
            for (int i = 0; i < encoded.size(); i++) {
                currentBits += encoded.getBit(i) ? '1' : '0';
                if (reverseMap.count(currentBits)) {
                    decoded += reverseMap[currentBits];
                    currentBits = "";
                }
            }
        } else {
            // Standard decoding using tree traversal
            std::shared_ptr<HuffmanNode> current = root;
            for (int i = 0; i < encoded.size(); i++) {
                if (encoded.getBit(i)) {
                    current = current->right;
                } else {
                    current = current->left;
                }

                if (current->isLeaf()) {
                    decoded += current->character;
                    current = root;
                }
            }
        }
        return decoded;
    }

    const std::map<char, BitSet>& getCodes() const {
        return codes;
    }

    const std::map<char, BitSet>& getCanonicalCodes() const {
        return canonicalCodes;
    }
};

#endif //HUFFMANTREE_H
