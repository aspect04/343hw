#include <iostream>
#include <string>
#include <vector>
#include "BitWriter.h"

using namespace std;

int main() {
    cout << "Running BitWriter Tests..." << endl << endl;

    // Test 1: Example from the requirements
    cout << "Test 1: Writing bits 1,0,1,0,1,0,1,0,1,0,1,0" << endl;
    BitWriter bw1;
    bw1.write(1); bw1.write(0); bw1.write(1); bw1.write(0);
    bw1.write(1); bw1.write(0); bw1.write(1); bw1.write(0);
    bw1.write(1); bw1.write(0); bw1.write(1); bw1.write(0);

    vector<uint8_t> result1;
    size_t bitCount1 = bw1.getData(result1);
    string hexStr1 = bw1.toHexString(result1, "-");

    cout << "  Bits written: " << bitCount1 << endl;
    cout << "  Hex output: " << hexStr1 << endl;
    cout << "  Expected: AA-A0" << endl;
    cout << "  PASS: " << (hexStr1 == "AA-A0" ? "YES" : "NO") << endl << endl;

    // Test 2: All ones (8 bits)
    cout << "Test 2: Writing 8 ones" << endl;
    BitWriter bw2;
    for (int i = 0; i < 8; i++) {
        bw2.write(1);
    }

    vector<uint8_t> result2;
    size_t bitCount2 = bw2.getData(result2);
    string hexStr2 = bw2.toHexString(result2);

    cout << "  Bits written: " << bitCount2 << endl;
    cout << "  Hex output: " << hexStr2 << endl;
    cout << "  Expected: FF" << endl;
    cout << "  PASS: " << (hexStr2 == "FF" ? "YES" : "NO") << endl << endl;

    // Test 3: All zeros (8 bits)
    cout << "Test 3: Writing 8 zeros" << endl;
    BitWriter bw3;
    for (int i = 0; i < 8; i++) {
        bw3.write(0);
    }

    vector<uint8_t> result3;
    size_t bitCount3 = bw3.getData(result3);
    string hexStr3 = bw3.toHexString(result3);

    cout << "  Bits written: " << bitCount3 << endl;
    cout << "  Hex output: " << hexStr3 << endl;
    cout << "  Expected: 00" << endl;
    cout << "  PASS: " << (hexStr3 == "00" ? "YES" : "NO") << endl << endl;

    // Test 4: Partial byte (5 bits)
    cout << "Test 4: Writing 5 bits: 1,0,1,1,0" << endl;
    BitWriter bw4;
    bw4.write(1); bw4.write(0); bw4.write(1); bw4.write(1); bw4.write(0);

    vector<uint8_t> result4;
    size_t bitCount4 = bw4.getData(result4);
    string hexStr4 = bw4.toHexString(result4);

    cout << "  Bits written: " << bitCount4 << endl;
    cout << "  Hex output: " << hexStr4 << endl;
    cout << "  Expected: B0 (10110000 in binary)" << endl;
    cout << "  PASS: " << (hexStr4 == "B0" ? "YES" : "NO") << endl << endl;

    // Test 5: Multiple bytes with delimiter
    cout << "Test 5: Writing 16 bits (alternating pattern) with ':' delimiter" << endl;
    BitWriter bw5;
    for (int i = 0; i < 16; i++) {
        bw5.write(i % 2);
    }

    vector<uint8_t> result5;
    size_t bitCount5 = bw5.getData(result5);
    string hexStr5 = bw5.toHexString(result5, ":");

    cout << "  Bits written: " << bitCount5 << endl;
    cout << "  Hex output: " << hexStr5 << endl;
    cout << "  Expected: 55:55" << endl;
    cout << "  PASS: " << (hexStr5 == "55:55" ? "YES" : "NO") << endl << endl;

    // Test 6: Empty BitWriter
    cout << "Test 6: Empty BitWriter (no bits written)" << endl;
    BitWriter bw6;
    vector<uint8_t> result6;
    size_t bitCount6 = bw6.getData(result6);
    string hexStr6 = bw6.toHexString(result6);

    cout << "  Bits written: " << bitCount6 << endl;
    cout << "  Hex output: '" << hexStr6 << "'" << endl;
    cout << "  Expected: '' (empty)" << endl;
    cout << "  PASS: " << (hexStr6.empty() ? "YES" : "NO") << endl << endl;

    // Test 7: Single bit (1)
    cout << "Test 7: Writing a single bit (1)" << endl;
    BitWriter bw7;
    bw7.write(1);

    vector<uint8_t> result7;
    size_t bitCount7 = bw7.getData(result7);
    string hexStr7 = bw7.toHexString(result7);

    cout << "  Bits written: " << bitCount7 << endl;
    cout << "  Hex output: " << hexStr7 << endl;
    cout << "  Expected: 80 (10000000 in binary)" << endl;
    cout << "  PASS: " << (hexStr7 == "80" ? "YES" : "NO") << endl << endl;

    // Test 8: Seven bits
    cout << "Test 8: Writing 7 bits: 1,1,1,1,1,1,1" << endl;
    BitWriter bw8;
    for (int i = 0; i < 7; i++) {
        bw8.write(1);
    }

    vector<uint8_t> result8;
    size_t bitCount8 = bw8.getData(result8);
    string hexStr8 = bw8.toHexString(result8);

    cout << "  Bits written: " << bitCount8 << endl;
    cout << "  Hex output: " << hexStr8 << endl;
    cout << "  Expected: FE (11111110 in binary)" << endl;
    cout << "  PASS: " << (hexStr8 == "FE" ? "YES" : "NO") << endl << endl;

    // Test 9: Three full bytes with pattern
    cout << "Test 9: Writing 24 bits (three bytes): 11110000 00001111 10101010" << endl;
    BitWriter bw9;
    // First byte: 11110000 = F0
    bw9.write(1); bw9.write(1); bw9.write(1); bw9.write(1);
    bw9.write(0); bw9.write(0); bw9.write(0); bw9.write(0);
    // Second byte: 00001111 = 0F
    bw9.write(0); bw9.write(0); bw9.write(0); bw9.write(0);
    bw9.write(1); bw9.write(1); bw9.write(1); bw9.write(1);
    // Third byte: 10101010 = AA
    bw9.write(1); bw9.write(0); bw9.write(1); bw9.write(0);
    bw9.write(1); bw9.write(0); bw9.write(1); bw9.write(0);

    vector<uint8_t> result9;
    size_t bitCount9 = bw9.getData(result9);
    string hexStr9 = bw9.toHexString(result9, " ");

    cout << "  Bits written: " << bitCount9 << endl;
    cout << "  Hex output: " << hexStr9 << endl;
    cout << "  Expected: F0 0F AA" << endl;
    cout << "  PASS: " << (hexStr9 == "F0 0F AA" ? "YES" : "NO") << endl << endl;

    // Test 10: Multi-character delimiter
    cout << "Test 10: Writing 16 bits with multi-character delimiter" << endl;
    BitWriter bw10;
    // First byte: 11001100 = CC
    bw10.write(1); bw10.write(1); bw10.write(0); bw10.write(0);
    bw10.write(1); bw10.write(1); bw10.write(0); bw10.write(0);
    // Second byte: 00110011 = 33
    bw10.write(0); bw10.write(0); bw10.write(1); bw10.write(1);
    bw10.write(0); bw10.write(0); bw10.write(1); bw10.write(1);

    vector<uint8_t> result10;
    size_t bitCount10 = bw10.getData(result10);
    string hexStr10 = bw10.toHexString(result10, " :: ");

    cout << "  Bits written: " << bitCount10 << endl;
    cout << "  Hex output: " << hexStr10 << endl;
    cout << "  Expected: CC :: 33" << endl;
    cout << "  PASS: " << (hexStr10 == "CC :: 33" ? "YES" : "NO") << endl << endl;

    return 0;
}
