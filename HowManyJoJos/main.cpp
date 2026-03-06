#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

// Structure to hold name data
struct NameData {
    string name;
    int count;
};

// Function to process a file and extract names starting with "Jo" for females
void processFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    // Regular expression pattern:
    // ^Jo      - starts with "Jo"
    // [^,]*    - followed by 0 or more characters that are not a comma
    // ,        - followed by a comma
    // F        - followed by F (female)
    // ,        - followed by a comma
    // (\d+)    - followed by 1 or more digits (capture group)
    regex pattern("^(Jo[^,]*),F,(\\d+)");
    smatch matches;

    vector<NameData> qualifyingNames;
    int totalChildren = 0;
    string line;

    // Process each line
    while (getline(file, line)) {
        // Remove carriage return if present (Windows line endings)
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (regex_match(line, matches, pattern)) {
            // Extract the name (first capture group)
            string name = matches[1].str();

            // Extract the count and convert to integer (second capture group)
            int count = stoi(matches[2].str());

            // Store the data
            qualifyingNames.push_back({name, count});
            totalChildren += count;
        }
    }

    file.close();

    // Print results
    cout << "=== Results for: " << filename << " ===" << endl;
    cout << "\nQualifying Names (starting with 'Jo', gender F):" << endl;
    cout << "------------------------------------------------" << endl;

    for (const auto& nameData : qualifyingNames) {
        cout << nameData.name << ": " << nameData.count << endl;
    }

    cout << "\n=== Summary ===" << endl;
    cout << "Number of qualifying names: " << qualifyingNames.size() << endl;
    cout << "Total children born with these names: " << totalChildren << endl;
    cout << endl;
}

int main() {
    // Test with smaller data file first
    cout << "TESTING WITH SMALL TEST DATA FILE:" << endl;
    cout << "==============================" << endl;
    processFile("test_data.txt");

    cout << "\n\nPROCESSING FULL yob2024 DATA FILE:" << endl;
    cout << "==============================" << endl;
    processFile("yob2024.txt");

    return 0;
}