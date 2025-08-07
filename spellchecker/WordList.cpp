#include "WordList.h"
#include "Heap.h"

#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>

WordList::WordList(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            words_.push_back(line);
        }
    }
}

std::string WordList::suggest(const std::vector<std::vector<int>>& input, int n) const {
    if (words_.empty()) return "";

    Heap topSuggestions(n); 

    for (const std::string& word : words_) {
        if (word.size() != input.size()) continue; 

        double dist = 0.0;

        for (size_t i = 0; i < word.size(); ++i) {
            char c = word[i];
            if (c < 'a' || c > 'z') {
                dist = std::numeric_limits<double>::max();
                break;
            }

            int index = c - 'a';
            int dx = input[i][0] - index;
            int dy = input[i][1] - index;
            dist += dx * dx + dy * dy;
        }

        if (dist < std::numeric_limits<double>::max()) {
            topSuggestions.push(word, dist);
        }
    }

    if (topSuggestions.empty()) return "";
    return topSuggestions.top();
}
