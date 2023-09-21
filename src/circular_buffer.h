#pragma once

#include <ostream>

template <typename T>
class CircularBuffer {
private:
public:
    CircularBuffer(int maxSize) {
    }

    int getSize() const {
        return 0;
    }

    void insert(int index, T element) {
    }

    void remove(int index) {
    }

    T& operator[](int index) {
        return {};
    }

    const T& operator[](int index) const {
        return {};
    }

    friend std::ostream &operator<<(std::ostream &strm, const CircularBuffer<T> &buffer) {
        for (int i = 0; i < buffer.getSize(); i++) {
            strm << buffer[i] << " ";
        }
        return strm;
    }
};
