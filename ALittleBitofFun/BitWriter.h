#ifndef BITWRITER_H
#define BITWRITER_H

#include <vector>
#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

class BitWriter {

public:
    BitWriter() : currentByte(0), bitCount(0), currentBitPosition(7) {}

    // adds a bit to the BitWriters internal state.
    void write(bool bitValue) {
        // Write to the current bit position (starting from MSB, position 7)
        if (bitValue) {
            currentByte |= (1 << currentBitPosition);
        }

        bitCount++;
        currentBitPosition--;

        // If we've filled a byte (all 8 bits written)
        if (currentBitPosition < 0) {
            buffer.push_back(currentByte);
            currentByte = 0;
            currentBitPosition = 7;
        }
    }

    // returns the number of bits written
    // all of the bits that have been written are returned in out
    size_t getData(std::vector<uint8_t>& out) {
        out = buffer;

        // If there are any remaining bits in the current byte, add it
        if (currentBitPosition < 7) {
            out.push_back(currentByte);
        }

        return bitCount;
    }

    // formats a vector<uint8_t> as a hexadecimal string
    // takes an optional delimiter value that is written after each byte
    std::string toHexString(std::vector<uint8_t> bytes, const std::string& delim = "") {
        std::stringstream ss;
        for (size_t i = 0; i < bytes.size(); i++) {
            ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0')
               << static_cast<int>(bytes[i]);
            if (!delim.empty() && i < bytes.size() - 1) {
                ss << delim;
            }
        }
        return ss.str();
    }
private:
    std::vector<uint8_t> buffer;
    uint8_t currentByte;
    size_t bitCount;
    int currentBitPosition;
};

#endif //BITWRITER_H