#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "BitSet.h"
#include "HuffmanTree.h"
#include "TestCases.cpp"

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

void printCodeTable(const map<char, BitSet>& codes) {
    vector<CodeEntry> entries;
    for (const auto& [ch, code] : codes) {
        entries.push_back({ch, code.size(), code});
    }

    sort(entries.begin(), entries.end(), compareCodeEntries);

    cout << "\nSymbol | Code\n";
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

int main(int argc, char* argv[]) {
    // Check if test flag is passed
    if (argc > 1 && string(argv[1]) == "--test") {
        return runAllTests();
    }

    // Assignment output: Process The Road passage
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

    // Print code table (sorted by code length ASC, symbol ASC)
    printCodeTable(canonicalCodes);

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

    cout << "\nCompressed size: " << bitsCompressed << " bits (" << bytesCompressed << " bytes)\n";
    cout << "Uncompressed size: " << bitsUncompressed << " bits (" << passage.length() << " bytes)\n";
    cout << "Compression ratio: " << fixed << setprecision(4) << compressionRatio << "\n";

    return 0;
}