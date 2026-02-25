#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

const int NUM_BUCKETS = 16;
const double SIGNIFICANCE_LEVEL = 0.05;
const double CHI_SQUARE_CRITICAL_VALUE = 24.996; // For df=15, alpha=0.05

// Hash function for strings
unsigned long hashFunction(const std::string& str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Extract name from CSV line (format: Name,Gender,Count)
std::string extractName(const std::string& line) {
    std::stringstream ss(line);
    std::string name;
    std::getline(ss, name, ',');
    return name;
}

// Chi-square test
bool performChiSquareTest(const std::vector<int>& bucketCounts, int totalNames) {
    double expectedPerBucket = static_cast<double>(totalNames) / NUM_BUCKETS;
    double chiSquare = 0.0;

    std::cout << "\nBucket Distribution:\n";
    std::cout << "-------------------\n";

    for (int i = 0; i < NUM_BUCKETS; i++) {
        std::cout << "Bucket " << i << ": " << bucketCounts[i] << " names\n";

        double observed = bucketCounts[i];
        double diff = observed - expectedPerBucket;
        chiSquare += (diff * diff) / expectedPerBucket;
    }

    std::cout << "\nChi-Square Test Results:\n";
    std::cout << "------------------------\n";
    std::cout << "Total names processed: " << totalNames << "\n";
    std::cout << "Expected per bucket: " << expectedPerBucket << "\n";
    std::cout << "Chi-square statistic: " << chiSquare << "\n";
    std::cout << "Critical value (df=15, alpha=0.05): " << CHI_SQUARE_CRITICAL_VALUE << "\n";

    return chiSquare > CHI_SQUARE_CRITICAL_VALUE;
}

int main() {
    std::ifstream file("yob2024.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open yob2024.txt\n";
        std::cerr << "Please download the file and place it in the project directory.\n";
        return 1;
    }

    std::vector<int> bucketCounts(NUM_BUCKETS, 0);
    std::string line;
    int totalNames = 0;

    // Process each line in the file
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::string name = extractName(line);
        if (name.empty()) continue;

        // Hash function and map to bucket
        unsigned long hashValue = hashFunction(name);
        int bucket = hashValue % NUM_BUCKETS;

        bucketCounts[bucket]++;
        totalNames++;
    }

    file.close();

    if (totalNames == 0) {
        std::cerr << "Error: No names were processed from the file.\n";
        return 1;
    }

    // Perform chi-square test
    bool isUnevenDistribution = performChiSquareTest(bucketCounts, totalNames);

    std::cout << "\nConclusion:\n";
    std::cout << "-----------\n";
    if (isUnevenDistribution) {
        std::cout << "The hash function is NOT evenly distributing the data.\n";
        std::cout << "(Chi-square statistic exceeds critical value at 0.05 significance level)\n";
    } else {
        std::cout << "The hash function appears to be evenly distributing the data.\n";
        std::cout << "(Failed to reject the null hypothesis at 0.05 significance level)\n";
    }

    return 0;
}