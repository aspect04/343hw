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
    for (const auto& pair : codes) {
        char ch = pair.first;
        const BitSet& code = pair.second;
        cout << "    " << ch << ": " << code.toBinaryString()
             << " (freq: " << frequencies[ch] << ")\n";
    }

    auto encoded = tree.encodeText(passage, true);
    auto decoded_size = passage.length() * 8;

    cout << "  Compression ratio: " << (double)encoded.size() / decoded_size << "\n";
}

void testRoundTrip() {
    cout << "\n========== TEST 8: Round-Trip (Self-Consistency) ==========\n";
    string passages[] = {
        "The quick brown fox jumps over the lazy dog.",
        "AAAABBBCCCDDEEF",
        "1234567890!@#$%^&*()",
        "Line 1\nLine 2\tTabbed"
    };

    for (const string& passage : passages) {
        HuffmanTree tree;
        auto freqs = tree.countFrequencies(passage);
        tree.buildTree(freqs);
        tree.generateCodes();
        tree.generateCanonicalCodes();

        // Test standard codes
        BitSet encoded = tree.encodeText(passage, false);
        string decoded = tree.decodeText(encoded, false);
        cout << "  Standard Round-Trip (\"" << (passage.length() > 20 ? passage.substr(0,17)+"..." : passage) << "\"): ";
        if (decoded == passage) cout << "PASSED\n";
        else cout << "FAILED (Got: " << decoded << ")\n";

        // Test canonical codes
        BitSet encodedCan = tree.encodeText(passage, true);
        string decodedCan = tree.decodeText(encodedCan, true);
        cout << "  Canonical Round-Trip: ";
        if (decodedCan == passage) cout << "PASSED\n";
        else cout << "FAILED\n";
    }
}

void testEmptyString() {
    cout << "\n========== TEST 9: Empty String ==========\n";
    HuffmanTree tree;
    string passage = "";
    auto freqs = tree.countFrequencies(passage);
    tree.buildTree(freqs);
    tree.generateCodes();
    
    BitSet encoded = tree.encodeText(passage);
    string decoded = tree.decodeText(encoded);
    
    cout << "  Empty string handling: ";
    if (encoded.size() == 0 && decoded == "") cout << "PASSED\n";
    else cout << "FAILED\n";
}

void testAll256Characters() {
    cout << "\n========== TEST 10: All 256 ASCII Characters ==========\n";
    string passage = "";
    for (int i = 0; i < 256; i++) {
        passage += (char)i;
    }

    HuffmanTree tree;
    auto freqs = tree.countFrequencies(passage);
    tree.buildTree(freqs);
    tree.generateCodes();
    tree.generateCanonicalCodes();

    BitSet encoded = tree.encodeText(passage, true);
    string decoded = tree.decodeText(encoded, true);

    cout << "  256-char Round-Trip: ";
    if (decoded == passage) cout << "PASSED\n";
    else cout << "FAILED\n";
}

void testBitBoundaries() {
    cout << "\n========== TEST 11: Bit Boundaries ==========\n";
    
    // Test 8 bits
    BitSet b8;
    for (int i = 0; i < 8; i++) b8.append(true);
    cout << "  8 bits: " << b8.size() << " bits, " << b8.sizeInBytes() << " bytes (Expected 8, 1): ";
    if (b8.size() == 8 && b8.sizeInBytes() == 1) cout << "PASSED\n";
    else cout << "FAILED\n";

    // Test 9 bits
    BitSet b9;
    for (int i = 0; i < 9; i++) b9.append(true);
    cout << "  9 bits: " << b9.size() << " bits, " << b9.sizeInBytes() << " bytes (Expected 9, 2): ";
    if (b9.size() == 9 && b9.sizeInBytes() == 2) cout << "PASSED\n";
    else cout << "FAILED\n";

    // Test 16 bits
    BitSet b16;
    for (int i = 0; i < 16; i++) b16.append(true);
    cout << "  16 bits: " << b16.size() << " bits, " << b16.sizeInBytes() << " bytes (Expected 16, 2): ";
    if (b16.size() == 16 && b16.sizeInBytes() == 2) cout << "PASSED\n";
    else cout << "FAILED\n";
}

void testUnbalancedTree() {
    cout << "\n========== TEST 12: Highly Unbalanced Tree ==========\n";
    // Frequencies: A=1, B=2, C=4, D=8, E=16, F=32, G=64
    string passage = "";
    int count = 1;
    for (char c = 'A'; c <= 'G'; c++) {
        for (int i = 0; i < count; i++) passage += c;
        count *= 2;
    }

    HuffmanTree tree;
    auto freqs = tree.countFrequencies(passage);
    tree.buildTree(freqs);
    tree.generateCodes();
    
    auto codes = tree.getCodes();
    cout << "  Deepest code length ('A'): " << codes['A'].size() << " (Expected 6): ";
    if (codes['A'].size() == 6) cout << "PASSED\n";
    else cout << "FAILED (Got " << codes['A'].size() << ")\n";

    string decoded = tree.decodeText(tree.encodeText(passage));
    cout << "  Unbalanced Round-Trip: ";
    if (decoded == passage) cout << "PASSED\n";
    else cout << "FAILED\n";
}

int testMain() {
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
    testRoundTrip();
    testEmptyString();
    testAll256Characters();
    testBitBoundaries();
    testUnbalancedTree();

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║          ALL TESTS COMPLETED                       ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
    cout << "\n";

    return 0;
}
