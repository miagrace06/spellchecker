#include "WordList.h"
#include <cmath>
#include <limits>

static float distanceSquared(const std::vector<Point>& a, const std::vector<Point>& b) {
    float sum = 0.0f;
    size_t n = a.size();
    for (size_t i = 0; i < n; ++i) {
        float dx = a[i].x - b[i].x;
        float dy = a[i].y - b[i].y;
        sum += dx * dx + dy * dy;
    }
    return sum;
}

WordList::WordList(std::istream& stream) {
    std::string line;
    while (std::getline(stream, line)) {
        if (!line.empty()) {
            mWords.push_back(line);
        }
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);

    for (const std::string& word : mWords) {
        if (word.length() != points.size()) continue;

        std::vector<Point> refPoints;
        for (char c : word) {
            refPoints.push_back(Point::fromChar(c));
        }

        float score = distanceSquared(points, refPoints);
        if (score < cutoff) {
            if (heap.count() < maxcount) {
                heap.push(word, score);
            } else {
                if (score < heap.top().score) {
                    heap.pushpop(word, score);
                }
            }
        }
    }

    return heap;
}
