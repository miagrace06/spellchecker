#include "Heap.h"
#include <stdexcept>
#include <cmath> 

Heap::Heap() {}

Heap::Heap(const Heap& other) {
    for (Entry* e : other.data_) {
        data_.push_back(new Entry(*e)); 
    }
}

Heap& Heap::operator=(const Heap& other) {
    if (this != &other) {
        clear(); 
        for (Entry* e : other.data_) {
            data_.push_back(new Entry(*e));
        }
    }
    return *this;
}

Heap::~Heap() {
    clear();
}

void Heap::clear() {
    for (Entry* e : data_) {
        delete e;
    }
    data_.clear();
}

bool Heap::isEmpty() const {
    return data_.empty();
}

int Heap::size() const {
    return static_cast<int>(data_.size());
}

const Entry& Heap::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    return *data_[0];
}

void Heap::push(Entry* e) {
    data_.push_back(e);
    percolateUp(data_.size() - 1);
}

Entry* Heap::removeMin() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }

    Entry* min = data_[0];

    data_[0] = data_.back();
    data_.pop_back();

    if (!isEmpty()) {
        percolateDown(0);
    }

    return min;
}

void Heap::percolateUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (*data_[index] < *data_[parent]) {
            std::swap(data_[index], data_[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void Heap::percolateDown(int index) {
    int size = static_cast<int>(data_.size());
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && *data_[left] < *data_[smallest]) {
            smallest = left;
        }
        if (right < size && *data_[right] < *data_[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            std::swap(data_[index], data_[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}
