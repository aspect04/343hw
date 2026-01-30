#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "BitSet.h"
#include "HuffmanTree.h"

using namespace std;

// Structure for sorting codes by length then character
struct CodeEntry {
    char character;
    int numBits;
    BitSet code;
};

bool compareCodeEntries(const CodeEntry& a, const CodeEntry& b) {
    if (a.numBits == b.numBits) {
        return a.character < b.character;
    }
    return a.numBits < b.numBits;
}

void printCodeTable(const map<char, BitSet>& codes, bool canonical) {
    vector<CodeEntry> entries;
    for (const auto& [ch, code] : codes) {
        entries.push_back({ch, code.size(), code});
    }

    sort(entries.begin(), entries.end(), compareCodeEntries);

    cout << "\n";
    if (canonical) {
        cout << "Canonical Huffman Codes:\n";
    } else {
        cout << "Huffman Codes:\n";
    }
    cout << "Symbol | Code\n";
    cout << "-------|----------\n";

    for (const auto& entry : entries) {
        // Handle special characters for display
        if (entry.character == '\n') {
            cout << "  \\n   | ";
        } else if (entry.character == '\t') {
            cout << "  \\t   | ";
        } else if (entry.character == ' ') {
            cout << " space | ";
        } else {
            cout << "   " << entry.character << "   | ";
        }
        cout << entry.code.toBinaryString() << "\n";
    }
}

void processTextAndEvaluate(const string& passage,
                           const map<char, int>& expectedCounts,
                           const map<char, BitSet>& expectedCodes,
                           const map<char, BitSet>& expectedCanonical,
                           const BitSet& expectedTextEncoding) {
    HuffmanTree tree;

    // Step 1: Count frequencies
    auto frequencies = tree.countFrequencies(passage);
    cout << "Frequency counting: ";
    if (frequencies == expectedCounts) {
        cout << "PASSED\n";
    } else {
        cout << "FAILED\n";
    }

    // Step 2: Build tree and generate codes
    tree.buildTree(frequencies);
    tree.generateCodes();
    auto codes = tree.getCodes();

    cout << "Code generation: ";
    if (codes == expectedCodes) {
        cout << "PASSED\n";
    } else {
        cout << "FAILED\n";
    }

    // Step 3: Generate canonical codes
    tree.generateCanonicalCodes();
    auto canonical = tree.getCanonicalCodes();

    cout << "Canonical codes: ";
    if (canonical == expectedCanonical) {
        cout << "PASSED\n";
    } else {
        cout << "FAILED\n";
    }

    // Step 4: Encode text
    auto encoded = tree.encodeText(passage, true);

    cout << "Text encoding: ";
    if (encoded.toBinaryString() == expectedTextEncoding.toBinaryString()) {
        cout << "PASSED\n";
    } else {
        cout << "FAILED\n";
        cout << "Expected: " << expectedTextEncoding.toBinaryString() << "\n";
        cout << "Got:      " << encoded.toBinaryString() << "\n";
    }
}

void testSimple() {
    cout << "\n========== TESTING SIMPLE CASE ==========\n";

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

void processTheRoad() {
    cout << "\n========== THE ROAD - HUFFMAN ENCODING ==========\n";

    string passage =
        "Once there were brook trouts in the streams in the mountains. "
        "You could see them standing in the amber current where the white edges of their fins "
        "wimpled softly in the flow. They smelled of moss in your hand. "
        "Polished and muscular and torsional. On their backs were vermiculate patterns "
        "that were maps of the world in its becoming. Maps and mazes. "
        "Of a thing which could not be put back. Not be made right again. "
        "In the deep glens where they lived all things were older than man and they hummed of mystery.";

    HuffmanTree tree;

    // Count frequencies
    auto frequencies = tree.countFrequencies(passage);

    // Build tree and generate codes
    tree.buildTree(frequencies);
    tree.generateCodes();

    // Generate canonical codes (extra credit)
    tree.generateCanonicalCodes();

    // Get canonical codes for output
    auto canonicalCodes = tree.getCanonicalCodes();

    // Print code table
    printCodeTable(canonicalCodes, true);

    // Encode the text using canonical codes
    auto encoded = tree.encodeText(passage, true);

    // Output first 8 bytes as binary
    cout << "\nFirst 8 bytes of encoded passage (binary):\n";
    string first8Bytes = encoded.getFirstNBytesAsBinary(8);
    for (size_t i = 0; i < first8Bytes.length(); i++) {
        cout << first8Bytes[i];
        if ((i + 1) % 8 == 0 && i + 1 < first8Bytes.length()) {
            cout << " ";
        }
    }
    cout << "\n";

    // Output size information
    int bitsCompressed = encoded.size();
    int bytesCompressed = encoded.sizeInBytes();
    int bitsUncompressed = passage.length() * 8;
    double compressionRatio = (double)bitsCompressed / (double)bitsUncompressed;

    cout << "\nCompression Statistics:\n";
    cout << "Compressed size: " << bitsCompressed << " bits (" << bytesCompressed << " bytes)\n";
    cout << "Uncompressed size: " << bitsUncompressed << " bits (" << passage.length() << " bytes)\n";
    cout << "Compression ratio: " << fixed << setprecision(4) << compressionRatio << "\n";
    cout << "Space savings: " << fixed << setprecision(2) << (1.0 - compressionRatio) * 100 << "%\n";
}

int main() {
    // Run the simple test case first
    testSimple();

    // Process The Road passage
    processTheRoad();

    return 0;
}