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
    if (mCount == 0) throw std::underflow_error("Heap is empty");
    Entry min = mData[0];
    Entry last = mData[--mCount];
    size_t i = 0;
    while (true) {
        size_t left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (left < mCount && mData[left].score < mData[smallest].score) smallest = left;
        if (right < mCount && mData[right].score < mData[smallest].score) smallest = right;
        if (smallest == i) break;
        mData[i] = mData[smallest];
        i = smallest;
    }
    mData[i] = last;
    return min;
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (mCount < mCapacity) {
        push(value, score);
        return pop();
    } else if (mCapacity == 0 || score >= mData[0].score) {
        Entry top = mData[0];
        mData[0] = {value, score};
        // Percolate down
        size_t i = 0;
        while (true) {
            size_t left = 2 * i + 1, right = 2 * i + 2, smallest = i;
            if (left < mCount && mData[left].score < mData[smallest].score) smallest = left;
            if (right < mCount && mData[right].score < mData[smallest].score) smallest = right;
            if (smallest == i) break;
            std::swap(mData[i], mData[smallest]);
            i = smallest;
        }
        return top;
    } else {
        return {value, score};
    }
}
