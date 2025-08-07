#include "WordList.h"
#include "Point.h"
#include <iostream>
#include <cmath>
#include <cctype>

WordList::WordList(std::istream& stream) {
    std::string line;
    while (std::getline(stream, line)) {
        if (line.empty()) continue;
        
        bool validWord = true;
        for (char c : line) {
            if (!islower(c)) {
                validWord = false;
                break;
            }
        }
        
        if (validWord) {
            mWords.push_back(line);
        }
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);
    
    for (const std::string& word : mWords) {
        if (word.length() != points.size()) {
            continue;
        }
        
        float totalScore = 0.0f;
        for (size_t i = 0; i < word.length(); ++i) {
            int letterIndex = word[i] - 'a';
            Point keyLocation = QWERTY[letterIndex];
            
            float dx = points[i].x - keyLocation.x;
            float dy = points[i].y - keyLocation.y;
            float distance = std::sqrt(dx * dx + dy * dy);
            
            float letterScore = 1.0f / (10.0f * distance * distance + 1.0f);
            totalScore += letterScore;
        }
        
        float averageScore = totalScore / word.length();
        
        if (averageScore >= cutoff) {
            if (heap.count() < maxcount) {
                heap.push(word, averageScore);
            } else {
                if (averageScore > heap.top().score) {
                    heap.pushpop(word, averageScore);
                }
            }
        }
    }
    
    return heap;
}
