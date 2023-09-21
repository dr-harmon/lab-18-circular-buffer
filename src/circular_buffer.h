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
public:
    CircularBuffer(int maxSize) {
        this->maxSize = maxSize;
        array = std::make_unique<T[]>(maxSize);
        length = 0;
    }

    int getSize() const {
        return length;
    }

    void insert(int index, T element) {
        if (index < 0 || index > length || length == maxSize) {
            throw std::out_of_range("Cannot insert");
        }
        for (int i = length - 1; i >= index; i--) {
            array[i + 1] = array[i];
        }
        array[index] = element;
        length++;
    }

    void remove(int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Cannot remove");
        }
        for (int i = index + 1; i < length; i++) {
            array[i - 1] = array[i];
        }
        length--;
    }

    T& operator[](int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Subscript out of bounds");
        }

        return array[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Subscript out of bounds");
        }

        return array[index];
    }

    friend std::ostream &operator<<(std::ostream &strm, const CircularBuffer<T> &buffer) {
        for (int i = 0; i < buffer.getSize(); i++) {
            strm << buffer[i] << " ";
        }
        return strm;
    }
};
