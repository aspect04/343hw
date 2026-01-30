#ifndef TESTCASES_H
#define TESTCASES_H

#include <iostream>
#include <string>
#include <map>
#include "BitSet.h"
#include "HuffmanTree.h"

using namespace std;

void processTextAndEvaluate(const string& passage,
                           const map<char, int>& expectedCounts,
                           const map<char, BitSet>& expectedCodes,
                           const map<char, BitSet>& expectedCanonical,
                           const BitSet& expectedTextEncoding) {
    HuffmanTree tree;

    // Step 1: Count frequencies
    auto frequencies = tree.countFrequencies(passage);
    cout << "  Frequency counting: ";
    if (frequencies == expectedCounts) {
        cout << "PASSED\n";
    } else {
        cout << "FAILED\n";
        cout << "    Expected " << expectedCounts.size() << " unique chars, got " << frequencies.size() << "\n";
    }

    // Step 2: Build tree and generate codes
    tree.buildTree(frequencies);
    tree.generateCodes();
    auto codes = tree.getCodes();

    cout << "  Code generation: ";
    if (codes == expectedCodes) {
        cout << "PASSED\n";
    } else {
        cout << "FAILED\n";
    }

    // Step 3: Generate canonical codes
    tree.generateCanonicalCodes();
    auto canonical = tree.getCanonicalCodes();

    cout << "  Canonical codes: ";
    if (canonical == expectedCanonical) {
        cout << "PASSED\n";
    } else {
        cout << "FAILED\n";
    }

    // Step 4: Encode text
    auto encoded = tree.encodeText(passage, true);

    cout << "  Text encoding: ";
    if (encoded.toBinaryString() == expectedTextEncoding.toBinaryString()) {
        cout << "PASSED\n";
    } else {
        cout << "FAILED\n";
        cout << "    Expected: " << expectedTextEncoding.toBinaryString() << "\n";
        cout << "    Got:      " << encoded.toBinaryString() << "\n";
    }
}

void testSimple() {
    cout << "\n========== TEST 1: Simple (Given) ==========\n";

    string passage = "AAAABBBCCCDDEEF";
    map<char,int> expectedCounts = { {'A', 4}, {'B', 3}, {'C', 3}, {'D',2}, {'E',2}, {'F',1} };
    map<char,BitSet> expectedCodes = { {'A',BitSet("10")},{'B',BitSet("111")},
                                       {'C',BitSet("00")},{'D',BitSet("011")},
                                       {'E',BitSet("110")},{'F',BitSet("010")}};

    map<char,BitSet> expectedCanonical = { {'A',BitSet("00")},{'B',BitSet("100")},
                                           {'C',BitSet("01")},{'D',BitSet("101")},
                                           {'E',BitSet("110")},{'F',BitSet("111")}};

    BitSet expectedTextEncoding("00000000100100100010101101101110110111");   // canonical

    processTextAndEvaluate(passage, expectedCounts, expectedCodes, expectedCanonical, expectedTextEncoding);
}

void testSingleCharacter() {
    cout << "\n========== TEST 2: Single Character ==========\n";

    HuffmanTree tree;
    string passage = "AAAA";

    auto frequencies = tree.countFrequencies(passage);
    cout << "  Frequency counting: ";
    if (frequencies.size() == 1 && frequencies['A'] == 4) {
        cout << "PASSED\n";
    } else {
        cout << "FAILED\n";
    }

    tree.buildTree(frequencies);
    tree.generateCodes();
    auto codes = tree.getCodes();

    // Single character should have a code (typically empty or single bit)
    cout << "  Code generation: ";
    if (codes.size() == 1) {
        cout << "PASSED (code length: " << codes['A'].size() << ")\n";
    } else {
        cout << "FAILED\n";
    }
}

void testTwoCharacters() {
    cout << "\n========== TEST 3: Two Characters ==========\n";

    string passage = "AABB";
    map<char,int> expectedCounts = { {'A', 2}, {'B', 2} };
    map<char,BitSet> expectedCodes = { {'A',BitSet("0")}, {'B',BitSet("1")} };
    map<char,BitSet> expectedCanonical = { {'A',BitSet("0")}, {'B',BitSet("1")} };
    BitSet expectedTextEncoding("0011");

    processTextAndEvaluate(passage, expectedCounts, expectedCodes, expectedCanonical, expectedTextEncoding);
}

void testAllSameFrequency() {
    cout << "\n========== TEST 4: Equal Frequencies ==========\n";

    HuffmanTree tree;
    string passage = "ABCD";

    auto frequencies = tree.countFrequencies(passage);
    cout << "  Frequency counting: ";
    if (frequencies.size() == 4 && frequencies['A'] == 1 && frequencies['B'] == 1
        && frequencies['C'] == 1 && frequencies['D'] == 1) {
        cout << "PASSED\n";
    } else {
        cout << "FAILED\n";
    }

    tree.buildTree(frequencies);
    tree.generateCodes();
    tree.generateCanonicalCodes();

    auto codes = tree.getCanonicalCodes();

    cout << "  Code generation: ";
    if (codes.size() == 4) {
        cout << "PASSED\n";
        cout << "    A: " << codes['A'].toBinaryString() << "\n";
        cout << "    B: " << codes['B'].toBinaryString() << "\n";
        cout << "    C: " << codes['C'].toBinaryString() << "\n";
        cout << "    D: " << codes['D'].toBinaryString() << "\n";
    } else {
        cout << "FAILED\n";
    }
}

void testWithSpacesAndPunctuation() {
    cout << "\n========== TEST 5: Spaces and Punctuation ==========\n";

    HuffmanTree tree;
    string passage = "Hello, World!";

    auto frequencies = tree.countFrequencies(passage);
    cout << "  Frequency counting: ";
    cout << "Found " << frequencies.size() << " unique characters\n";

    tree.buildTree(frequencies);
    tree.generateCodes();
    tree.generateCanonicalCodes();

    auto encoded = tree.encodeText(passage, true);
    auto decoded_size = passage.length() * 8;

    cout << "  Compression: " << encoded.size() << " bits vs " << decoded_size << " bits\n";
    cout << "  Ratio: " << (double)encoded.size() / decoded_size << "\n";
}

void testLongerText() {
    cout << "\n========== TEST 6: Longer Text ==========\n";

    HuffmanTree tree;
    string passage = "The quick brown fox jumps over the lazy dog.";

    auto frequencies = tree.countFrequencies(passage);
    cout << "  Frequency counting: Found " << frequencies.size() << " unique characters\n";

    tree.buildTree(frequencies);
    tree.generateCodes();
    tree.generateCanonicalCodes();

    auto encoded = tree.encodeText(passage, true);
    auto decoded_size = passage.length() * 8;

    cout << "  Original size: " << decoded_size << " bits (" << passage.length() << " bytes)\n";
    cout << "  Compressed size: " << encoded.size() << " bits (" << encoded.sizeInBytes() << " bytes)\n";
    cout << "  Compression ratio: " << (double)encoded.size() / decoded_size << "\n";
}

void testRepeatedPattern() {
    cout << "\n========== TEST 7: Highly Repetitive Text ==========\n";

    HuffmanTree tree;
    string passage = "AAAAAAAAAAAABBBBCCCCDDEE";

    auto frequencies = tree.countFrequencies(passage);
    tree.buildTree(frequencies);
    tree.generateCodes();
    tree.generateCanonicalCodes();

    auto codes = tree.getCanonicalCodes();

    cout << "  Character codes:\n";
    for (const auto& [ch, code] : codes) {
        cout << "    " << ch << ": " << code.toBinaryString()
             << " (freq: " << frequencies[ch] << ")\n";
    }

    auto encoded = tree.encodeText(passage, true);
    auto decoded_size = passage.length() * 8;

    cout << "  Compression ratio: " << (double)encoded.size() / decoded_size << "\n";
}

int runAllTests() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║          HUFFMAN CODING TEST SUITE                 ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";

    testSimple();
    testSingleCharacter();
    testTwoCharacters();
    testAllSameFrequency();
    testWithSpacesAndPunctuation();
    testLongerText();
    testRepeatedPattern();

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║          ALL TESTS COMPLETED                       ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
    cout << "\n";

    return 0;
}

#endif // TESTCASES_H