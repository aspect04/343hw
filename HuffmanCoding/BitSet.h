#ifndef BITSET_H
#define BITSET_H

#include <string>
#include <vector>
#include <cstdint>
#include <sstream>
#include <iomanip>

class BitSet {
private:
    std::vector<uint8_t> bytes;
    int numBits;

public:
    BitSet() : numBits(0) {}

    BitSet(const std::string& bitString) : numBits(0) {
        for (char c : bitString) {
            if (c == '1') {
                append(true);
            } else if (c == '0') {
                append(false);
            }
        }
    }

    void append(bool bit) {
        if (numBits % 8 == 0) {
            bytes.push_back(0);
        }

        if (bit) {
            int byteIndex = numBits / 8;
            int bitIndex = 7 - (numBits % 8);
            bytes[byteIndex] |= (1 << bitIndex);
        }

        numBits++;
    }

    void append(const BitSet& other) {
        for (int i = 0; i < other.numBits; i++) {
            append(other.getBit(i));
        }
    }

    bool getBit(int index) const {
        if (index >= numBits) return false;

        int byteIndex = index / 8;
        int bitIndex = 7 - (index % 8);
        return (bytes[byteIndex] & (1 << bitIndex)) != 0;
    }

    int size() const {
        return numBits;
    }

    int sizeInBytes() const {
        return (numBits + 7) / 8;
    }

    std::string toBinaryString() const {
        std::string result;
        for (int i = 0; i < numBits; i++) {
            result += getBit(i) ? '1' : '0';
        }
        return result;
    }

    std::string toHexString(int numBytes = -1) const {
        if (numBytes == -1) {
            numBytes = sizeInBytes();
        }

        std::stringstream ss;
        for (int i = 0; i < numBytes && i < (int)bytes.size(); i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)bytes[i];
        }
        return ss.str();
    }

    std::string getFirstNBytesAsBinary(int n) const {
        std::string result;
        for (int i = 0; i < n * 8 && i < numBits; i++) {
            result += getBit(i) ? '1' : '0';
        }
        return result;
    }

    const std::vector<uint8_t>& getBytes() const {
        return bytes;
    }

    bool operator==(const BitSet& other) const {
        if (numBits != other.numBits) return false;
        for (int i = 0; i < numBits; i++) {
            if (getBit(i) != other.getBit(i)) return false;
        }
        return true;
    }

    bool operator!=(const BitSet& other) const {
        return !(*this == other);
    }
};

#endif //BITSET_H