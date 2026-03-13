#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <map>
#include <string>

/**
 * Counts the frequencies of each character in a given text.
 * @param text The input passage to analyze.
 * @return A map of characters and their corresponding frequencies.
 */
inline std::map<char, int> countFrequencies(const std::string& text) {
    std::map<char, int> frequencies;
    for (char c : text) {
        frequencies[c]++;
    }
    return frequencies;
}

#endif // FREQUENCY_H
