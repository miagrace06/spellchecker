#include "Heap.h"
#include <stdexcept>
#include <utility>

Heap::Heap(size_t capacity)
    : mData(new Entry[capacity]), mCapacity(capacity), mCount(0) {}

Heap::Heap(const Heap& other)
    : mData(new Entry[other.mCapacity]), mCapacity(other.mCapacity), mCount(other.mCount) {
    for (size_t i = 0; i < mCount; ++i) {
        mData[i] = other.mData[i];
    }
}

Heap::Heap(Heap&& other)
    : mData(other.mData), mCapacity(other.mCapacity), mCount(other.mCount) {
    other.mData = nullptr;
    other.mCapacity = 0;
    other.mCount = 0;
}

Heap::~Heap() {
    delete[] mData;
}

size_t Heap::capacity() const {
    return mCapacity;
}

size_t Heap::count() const {
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const {
    if (index >= mCount) throw std::out_of_range("Index out of bounds");
    return mData[index];
}

const Heap::Entry& Heap::top() const {
    if (mCount == 0) throw std::underflow_error("Heap is empty");
    return mData[0];
}

void Heap::push(const std::string& value, float score) {
    if (mCount >= mCapacity) throw std::overflow_error("Heap is full");
    size_t i = mCount++;
    while (i > 0) {
        size_t parent = (i - 1) / 2;
        if (score >= mData[parent].score) break;
        mData[i] = mData[parent];
        i = parent;
    }
    mData[i] = {value, score};
}

Heap::Entry Heap::pop() {
    if (mCount == 0) {
        std::cout << "Underflow." << std::endl;
        return Entry{"", 0};
    }
    Entry topEntry = mData[0];
    mData[0] = mData[mCount - 1];
    mCount--;
    percolateDown(0);
    std::cout << "popped (" << topEntry.value << " " << topEntry.score << ")" << std::endl;
    return topEntry;
}


Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (mCount == 0) {
        std::cout << "Underflow." << std::endl;
        return Entry{"", 0};
    }

    Entry oldTop = mData[0];

    if (score > oldTop.score) {
        mData[0] = Entry{value, score};
        percolateDown(0);
    } else {
        // New score is smaller or equal — don't insert, just return
    }

    std::cout << "popped (" << oldTop.value << " " << oldTop.score << ")" << std::endl;
    return oldTop;
}

