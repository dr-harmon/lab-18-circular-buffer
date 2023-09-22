#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>

#include "circular_buffer.h"
#include <vector>

using namespace std;

const int SIZE = 5;

void requireEqual(const CircularBuffer<int>& b, const vector<int>& v)
{
    for (int i = 0; i < v.size(); i++) {
        REQUIRE(b[i] == v[i]);
    }
}

TEST_CASE("Elements can be inserted at the end")
{
    CircularBuffer<int> buffer(SIZE);
    for (int i = 1; i <= SIZE; i++) {
        buffer.insert(i - 1, i);
        REQUIRE(buffer.getSize() == i);
    }
    requireEqual(buffer, {1, 2, 3, 4, 5});
}

TEST_CASE("Elements can be inserted at the beginning")
{
    CircularBuffer<int> buffer(SIZE);
    for (int i = SIZE; i >= 1; i--) {
        buffer.insert(0, i);
        REQUIRE(buffer.getSize() == SIZE - i + 1);
    }
    requireEqual(buffer, {1, 2, 3, 4, 5});
}

TEST_CASE("Elements can be inserted in the middle")
{
    CircularBuffer<int> buffer(SIZE);
    buffer.insert(0, 1);
    buffer.insert(1, 3);
    buffer.insert(2, 5);
    buffer.insert(1, 2);
    buffer.insert(3, 4);

    requireEqual(buffer, {1, 2, 3, 4, 5});
}

TEST_CASE("Inserting an out-of-bounds index throws an exception")
{
    CircularBuffer<int> buffer(SIZE);

    for (int i = 1; i <= SIZE; i++) {
        buffer.insert(i - 1, i);
    }
    requireEqual(buffer, {1, 2, 3, 4, 5});

    REQUIRE_THROWS(buffer.insert(-1, 42));
    REQUIRE_THROWS(buffer.insert(SIZE, 42));
}

TEST_CASE("Elements can be removed from the end")
{
    CircularBuffer<int> buffer(SIZE);

    for (int i = 1; i <= SIZE; i++) {
        buffer.insert(i - 1, i);
    }
    requireEqual(buffer, {1, 2, 3, 4, 5});

    for (int i = SIZE - 1; i >= 0; i--) {
        buffer.remove(i);
        REQUIRE(buffer.getSize() == i);
    }
}

TEST_CASE("Elements can be removed from the beginning")
{
    CircularBuffer<int> buffer(SIZE);

    for (int i = 1; i <= SIZE; i++) {
        buffer.insert(i - 1, i);
    }
    requireEqual(buffer, {1, 2, 3, 4, 5});

    for (int i = SIZE - 1; i >= 0; i--) {
        buffer.remove(0);
        REQUIRE(buffer.getSize() == i);
    }
}

TEST_CASE("Elements can be removed from the middle")
{
    CircularBuffer<int> buffer(SIZE);

    for (int i = 1; i <= SIZE; i++) {
        buffer.insert(i - 1, i);
    }
    requireEqual(buffer, {1, 2, 3, 4, 5});

    buffer.remove(1);
    requireEqual(buffer, {1, 3, 4, 5});

    buffer.remove(2);
    requireEqual(buffer, {1, 3, 5});
}

TEST_CASE("Removing an out-of-bounds index throws an exception")
{
    CircularBuffer<int> buffer(SIZE);

    for (int i = 1; i <= SIZE; i++) {
        buffer.insert(i - 1, i);
    }
    requireEqual(buffer, {1, 2, 3, 4, 5});

    REQUIRE_THROWS(buffer.remove(-1));
    REQUIRE_THROWS(buffer.remove(SIZE));
}

TEST_CASE("Elements can be accessed by index")
{
    CircularBuffer<int> buffer(SIZE);

    for (int i = 1; i <= SIZE; i++) {
        buffer.insert(i - 1, i);
    }
    requireEqual(buffer, {1, 2, 3, 4, 5});

    REQUIRE(buffer[0] == 1);
    REQUIRE(buffer[SIZE-1] == SIZE);
    REQUIRE_THROWS(buffer[-1]);
    REQUIRE_THROWS(buffer[SIZE]);
}

TEST_CASE("Elements can be set by index")
{
    CircularBuffer<int> buffer(SIZE);

    for (int i = 1; i <= SIZE; i++) {
        buffer.insert(i - 1, i);
    }
    requireEqual(buffer, {1, 2, 3, 4, 5});

    buffer[0] = 99;
    buffer[SIZE-1] = 101;
    REQUIRE(buffer[0] == 99);
    REQUIRE(buffer[SIZE-1] == 101);
    REQUIRE_THROWS(buffer[-1] = 99);
    REQUIRE_THROWS(buffer[SIZE] = 99);
}
