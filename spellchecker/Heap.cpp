#include "Heap.h"
#include <utility> 
#include <string>  

Heap::Heap() {}

void Heap::push(std::pair<std::string, double> newValue) {
    heap.push_back(newValue);
    int index = heap.size() - 1;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].second < heap[parent].second) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

std::pair<std::string, double> Heap::pop() {
    if (heap.empty()) {
        return std::make_pair("", -1.0);
    }

    std::pair<std::string, double> minElement = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    percolateDown(0);
    return minElement;
}

void Heap::percolateDown(int index) {
    int size = heap.size();

    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left].second < heap[smallest].second) {
            smallest = left;
        }
        if (right < size && heap[right].second < heap[smallest].second) {
            smallest = right;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

bool Heap::isEmpty() const {
    return heap.empty();
}
