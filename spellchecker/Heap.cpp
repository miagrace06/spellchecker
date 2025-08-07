#include "Heap.h"
#include <stdexcept>
#include <utility>

Heap::Heap(size_t capacity) : mCapacity(capacity), mCount(0) {
    mData = new Entry[mCapacity];
}

Heap::Heap(const Heap& other) : mCapacity(other.mCapacity), mCount(other.mCount) {
    mData = new Entry[mCapacity];
    for (size_t i = 0; i < mCount; ++i) {
        mData[i] = other.mData[i];
    }
}

Heap::Heap(Heap&& other) : mData(other.mData), mCapacity(other.mCapacity), mCount(other.mCount) {
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
    if (index >= mCount) {
        throw std::out_of_range("Index out of range");
    }
    return mData[index];
}

const Heap::Entry& Heap::top() const {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    return mData[0];
}

void Heap::push(const std::string& value, float score) {
    if (mCount >= mCapacity) {
        throw std::overflow_error("Heap is full");
    }
    
    mData[mCount].value = value;
    mData[mCount].score = score;
    
    size_t index = mCount;
    mCount++;
    
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (mData[index].score < mData[parent].score) {
            std::swap(mData[index], mData[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

Heap::Entry Heap::pop() {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    
    Entry result = mData[0];
    
    mCount--;
    if (mCount > 0) {
        mData[0] = mData[mCount];
        percolateDown(0);
    }
    
    return result;
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    
    Entry result = mData[0];
    
    mData[0].value = value;
    mData[0].score = score;
    percolateDown(0);
    
    return result;
}

void Heap::percolateDown(size_t index) {
    while (true) {
        size_t left = index * 2 + 1;
        size_t right = index * 2 + 2;
        size_t smallest = index;
        
        if (left < mCount && mData[left].score < mData[smallest].score) {
            smallest = left;
        }
        if (right < mCount && mData[right].score < mData[smallest].score) {
            smallest = right;
        }
        
        if (left < mCount && right < mCount && 
            mData[left].score == mData[right].score && 
            mData[left].score < mData[index].score) {
            smallest = left;
        }
        
        if (smallest != index) {
            std::swap(mData[index], mData[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}
