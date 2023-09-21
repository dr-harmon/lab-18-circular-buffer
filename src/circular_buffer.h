#pragma once

#include <ostream>
#include <memory>
#include <stdexcept>

template <typename T>
class CircularBuffer {
private:
    int maxSize;
    std::unique_ptr<T[]> array;
    int length;
    int start;
public:
    CircularBuffer(int maxSize) {
        this->maxSize = maxSize;
        array = std::make_unique<T[]>(maxSize);
        length = 0;
        start = 0;
    }

    int getSize() const {
        return length;
    }

    void insert(int index, T element) {
        if (index < 0 || index > length || length == maxSize) {
            throw std::out_of_range("Cannot insert");
        }
        if (index == 0) {
            start--;
            if (start == -1) {  // Protect against underflow
                start = maxSize - 1;
            }
        } else {
            for (int i = length - 1; i >= index; i--) {
                array[(start + i + 1) % maxSize] = array[(start + i) % maxSize];
            }
        }
        array[(start + index) % maxSize] = element;
        length++;
    }

    void remove(int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Cannot remove");
        }
        if (index == 0) {
            start++;
            if (start == maxSize) {  // Protect against overflow
                start = 0;
            }
        } else {
            for (int i = index + 1; i < length; i++) {
                array[(start + i - 1) % maxSize] = array[(start + i) % maxSize];
            }
        }
        length--;
    }

    T& operator[](int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Subscript out of bounds");
        }

        return array[(start + index) % maxSize];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Subscript out of bounds");
        }

        return array[(start + index) % maxSize];
    }

    friend std::ostream &operator<<(std::ostream &strm, const CircularBuffer<T> &buffer) {
        for (int i = 0; i < buffer.getSize(); i++) {
            strm << buffer[i] << " ";
        }
        return strm;
    }
};
