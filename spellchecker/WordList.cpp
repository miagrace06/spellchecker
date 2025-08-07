#include "WordList.h"
#include "Heap.h"

#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>

WordList::WordList(std::istream& stream) {
    std::string word;
    while (stream >> word) {
        mWords.push_back(word);
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
