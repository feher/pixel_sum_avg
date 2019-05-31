#include <iostream>
#include <memory>
#include <cstddef>
#include <cstdlib>
#include <chrono>

#include "TestHelper.hpp"
#include "../PixelSum.hpp"

template <typename T>
void printElapsedTime(const char* functionName, const char *message, const T& startTime, const T& endTime) {
    const auto millis = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() / 1000000.0;
    std::cout << functionName << ": " << message << ": " << millis << " ms" << std::endl;
}

void test_getPixelSum() {
    const auto width = 4096;
    const auto height = 4096;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3});

    auto startTime = std::chrono::steady_clock::now();
    const auto ps = PixelSum{buffer.get(), width, height};
    auto endTime = std::chrono::steady_clock::now();
    printElapsedTime(__func__, "Init: ", startTime, endTime);

    startTime = std::chrono::steady_clock::now();
    const auto w = 4;
    const auto h = 4;
    for (int y = 0; y <= height - h; ++y) {
        for (int x = 0; x <= width - w; ++x) {
            const auto result = ps.getPixelSum(x, y, x + w - 1, y + h - 1);
            TEST_ASSERT_EQ(result, (0 + 1 + 2 + 3) * h);
        }
    }
    endTime = std::chrono::steady_clock::now();
    printElapsedTime(__func__, "Loop: ", startTime, endTime);
}

void test_getPixelAverage() {
    const auto width = 4096;
    const auto height = 4096;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3});

    auto startTime = std::chrono::steady_clock::now();
    const auto ps = PixelSum{buffer.get(), width, height};
    auto endTime = std::chrono::steady_clock::now();
    printElapsedTime(__func__, "Init: ", startTime, endTime);

    startTime = std::chrono::steady_clock::now();
    const auto w = 4;
    const auto h = 4;
    for (int y = 0; y <= height - h; ++y) {
        for (int x = 0; x <= width - w; ++x) {
            const auto result = ps.getPixelAverage(x, y, x + w - 1, y + h - 1);
            TEST_ASSERT_EQ(result, (0 + 1 + 2 + 3) * h / static_cast<double>(w * h));
        }
    }
    endTime = std::chrono::steady_clock::now();
    printElapsedTime(__func__, "Loop: ", startTime, endTime);
}

void test_getNonZeroCount() {
    const auto width = 4096;
    const auto height = 4096;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3});

    auto startTime = std::chrono::steady_clock::now();
    const auto ps = PixelSum{buffer.get(), width, height};
    auto endTime = std::chrono::steady_clock::now();
    printElapsedTime(__func__, "Init: ", startTime, endTime);

    startTime = std::chrono::steady_clock::now();
    const auto w = 4;
    const auto h = 4;
    for (int y = 0; y <= height - h; ++y) {
        for (int x = 0; x <= width - w; ++x) {
            const auto result = ps.getNonZeroCount(x, y, x + w - 1, y + h - 1);
            TEST_ASSERT_EQ(result, 3 * h);
        }
    }
    endTime = std::chrono::steady_clock::now();
    printElapsedTime(__func__, "Loop: ", startTime, endTime);
}

void test_getNonZeroAverage() {
    const auto width = 4096;
    const auto height = 4096;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3});

    auto startTime = std::chrono::steady_clock::now();
    const auto ps = PixelSum{buffer.get(), width, height};
    auto endTime = std::chrono::steady_clock::now();
    printElapsedTime(__func__, "Init: ", startTime, endTime);

    startTime = std::chrono::steady_clock::now();
    const auto w = 4;
    const auto h = 4;
    for (int y = 0; y <= height - h; ++y) {
        for (int x = 0; x <= width - w; ++x) {
            const auto result = ps.getNonZeroAverage(x, y, x + w - 1, y + h - 1);
            TEST_ASSERT_EQ(result, (0 + 1 + 2 + 3) * h / (3.0 * h));
        }
    }
    endTime = std::chrono::steady_clock::now();
    printElapsedTime(__func__, "Loop: ", startTime, endTime);
}

int main() {
    test_getPixelSum();
    test_getPixelAverage();
    test_getNonZeroCount();
    test_getNonZeroAverage();
}
