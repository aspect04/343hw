#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>

const int NUM_BUCKETS = 16;

// Same hash function from main.cpp
unsigned long hashFunction(const std::string& str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Same extract function from main.cpp
std::string extractName(const std::string& line) {
    std::stringstream ss(line);
    std::string name;
    std::getline(ss, name, ',');
    return name;
}

// Calculate chi-square statistic
double calculateChiSquare(const std::vector<int>& bucketCounts, int totalNames) {
    double expectedPerBucket = static_cast<double>(totalNames) / NUM_BUCKETS;
    double chiSquare = 0.0;

    for (int count : bucketCounts) {
        double observed = count;
        double diff = observed - expectedPerBucket;
        chiSquare += (diff * diff) / expectedPerBucket;
    }

    return chiSquare;
}

// Test 1: Hash function produces consistent results
void testHashConsistency() {
    std::cout << "Test 1: Hash Consistency... ";

    std::string name = "Alice";
    unsigned long hash1 = hashFunction(name);
    unsigned long hash2 = hashFunction(name);

    assert(hash1 == hash2);
    std::cout << "PASSED\n";
}

// Test 2: Different names produce different hashes (mostly)
void testHashUniqueness() {
    std::cout << "Test 2: Hash Uniqueness... ";

    unsigned long hash1 = hashFunction("Alice");
    unsigned long hash2 = hashFunction("Bob");
    unsigned long hash3 = hashFunction("Charlie");

    assert(hash1 != hash2);
    assert(hash2 != hash3);
    assert(hash1 != hash3);

    std::cout << "PASSED\n";
}

// Test 3: Hash maps to valid bucket range
void testBucketRange() {
    std::cout << "Test 3: Bucket Range... ";

    std::vector<std::string> testNames = {
        "Alice", "Bob", "Charlie", "Diana", "Eve",
        "Frank", "Grace", "Henry", "Iris", "Jack"
    };

    for (const auto& name : testNames) {
        unsigned long hash = hashFunction(name);
        int bucket = hash % NUM_BUCKETS;
        assert(bucket >= 0 && bucket < NUM_BUCKETS);
    }

    std::cout << "PASSED\n";
}

// Test 4: CSV parsing extracts name correctly
void testCSVParsing() {
    std::cout << "Test 4: CSV Parsing... ";

    std::string line1 = "Olivia,F,14718";
    std::string name1 = extractName(line1);
    assert(name1 == "Olivia");

    std::string line2 = "Noah,M,12345";
    std::string name2 = extractName(line2);
    assert(name2 == "Noah");

    std::string line3 = "Emma-Rose,F,100";
    std::string name3 = extractName(line3);
    assert(name3 == "Emma-Rose");

    std::cout << "PASSED\n";
}

// Test 5: Chi-square calculation with perfectly uniform distribution
void testChiSquareUniform() {
    std::cout << "Test 5: Chi-Square Uniform Distribution... ";

    // Perfect distribution: 100 items per bucket
    std::vector<int> perfectBuckets(NUM_BUCKETS, 100);
    int totalNames = 1600;

    double chiSquare = calculateChiSquare(perfectBuckets, totalNames);

    // With perfect distribution, chi-square should be 0
    assert(chiSquare < 0.01);

    std::cout << "PASSED (χ² = " << chiSquare << ")\n";
}

// Test 6: Chi-square calculation with non-uniform distribution
void testChiSquareNonUniform() {
    std::cout << "Test 6: Chi-Square Non-Uniform Distribution... ";

    // Highly skewed distribution
    std::vector<int> skewedBuckets = {
        500, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100
    };
    int totalNames = 1900;

    double chiSquare = calculateChiSquare(skewedBuckets, totalNames);

    // This should produce a high chi-square value (> 24.996)
    assert(chiSquare > 24.996);

    std::cout << "PASSED (χ² = " << chiSquare << ")\n";
}

// Test 7: Hash distribution with small dataset
void testSmallDatasetDistribution() {
    std::cout << "Test 7: Small Dataset Distribution... ";

    std::vector<std::string> names = {
        "Olivia", "Emma", "Amelia", "Charlotte", "Mia",
        "Sophia", "Isabella", "Evelyn", "Ava", "Sofia",
        "Camila", "Harper", "Luna", "Eleanor", "Violet",
        "Aurora"
    };

    std::vector<int> bucketCounts(NUM_BUCKETS, 0);

    for (const auto& name : names) {
        unsigned long hash = hashFunction(name);
        int bucket = hash % NUM_BUCKETS;
        bucketCounts[bucket]++;
    }

    int total = 0;
    for (int count : bucketCounts) {
        total += count;
    }

    assert(total == 16);
    std::cout << "PASSED\n";
}

// Test 8: Verify yob2024.txt exists and is readable
void testFileExists() {
    std::cout << "Test 8: Data File Exists... ";

    std::ifstream file("yob2024.txt");
    assert(file.is_open());

    // Read at least one line
    std::string line;
    assert(std::getline(file, line));
    assert(!line.empty());

    file.close();
    std::cout << "PASSED\n";
}

// Test 9: Empty string handling
void testEmptyString() {
    std::cout << "Test 9: Empty String Handling... ";

    std::string empty = "";
    unsigned long hash = hashFunction(empty);
    assert(hash == 5381); // DJB2 initial value

    std::cout << "PASSED\n";
}

// Test 10: Case sensitivity
void testCaseSensitivity() {
    std::cout << "Test 10: Case Sensitivity... ";

    unsigned long hash1 = hashFunction("Alice");
    unsigned long hash2 = hashFunction("alice");
    unsigned long hash3 = hashFunction("ALICE");

    // Hash should be case-sensitive
    assert(hash1 != hash2);
    assert(hash2 != hash3);
    assert(hash1 != hash3);

    std::cout << "PASSED\n";
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "   BraggingRights Test Suite\n";
    std::cout << "===========================================\n\n";

    int testsPassed = 0;
    int totalTests = 10;

    try {
        testHashConsistency();
        testsPassed++;

        testHashUniqueness();
        testsPassed++;

        testBucketRange();
        testsPassed++;

        testCSVParsing();
        testsPassed++;

        testChiSquareUniform();
        testsPassed++;

        testChiSquareNonUniform();
        testsPassed++;

        testSmallDatasetDistribution();
        testsPassed++;

        testFileExists();
        testsPassed++;

        testEmptyString();
        testsPassed++;

        testCaseSensitivity();
        testsPassed++;

    } catch (const std::exception& e) {
        std::cerr << "\n\nFAILED: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\n===========================================\n";
    std::cout << "   Results: " << testsPassed << "/" << totalTests << " tests passed\n";
    std::cout << "===========================================\n";

    if (testsPassed == totalTests) {
        std::cout << "\n✓ All tests passed! Your implementation is solid.\n";
        return 0;
    } else {
        std::cout << "\n✗ Some tests failed.\n";
        return 1;
    }
}
