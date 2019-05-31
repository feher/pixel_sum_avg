#include <iostream>
#include <memory>
#include <random>
#include <functional>

#include <cstddef>
#include <cstdlib>

#include "TestHelper.hpp"
#include "../PixelSum.hpp"

constexpr int bufferWidth = 4096;
constexpr int bufferHeight = 4096;
constexpr int iterationCount = 10000000;

int test_func(std::function<int(const PixelSum&, int, int, int, int)> func) {
    auto result = 0;
    const auto width = bufferWidth;
    const auto height = bufferHeight;
    const auto buffer = makeTestBuffer(width, height);
    const auto ps = PixelSum{buffer.get(), width, height};

    auto randDevice = std::random_device{};
    auto randEngine = std::mt19937{randDevice()};
    auto randDistX = std::uniform_int_distribution<int>{-(width / 2), width + (width / 2)};
    auto randDistY = std::uniform_int_distribution<int>{-(height / 2), height + (height / 2)};

    for (int i = 0; i < iterationCount; ++i) {
        const auto x = randDistX(randEngine);
        const auto y = randDistY(randEngine);
        const auto w = randDistX(randEngine);
        const auto h = randDistY(randEngine);
        result = func(ps, x, y, x + w, y + h);
    }
    return result;
}

int main() {
    auto result = test_func([] (const PixelSum& ps, int x0, int y0, int x1, int y1) {
        return ps.getPixelSum(x0, y0, x1, y1);
    });
    result += test_func([] (const PixelSum& ps, int x0, int y0, int x1, int y1) {
        return ps.getPixelAverage(x0, y0, x1, y1);
    });
    result += test_func([] (const PixelSum& ps, int x0, int y0, int x1, int y1) {
        return ps.getNonZeroCount(x0, y0, x1, y1);
    });
    result += test_func([] (const PixelSum& ps, int x0, int y0, int x1, int y1) {
        return ps.getNonZeroAverage(x0, y0, x1, y1);
    });
    result += test_func([] (const PixelSum& ps, int x0, int y0, int x1, int y1) {
        return ps.getPixelSum(x0, y0, x1, y1)
               + ps.getPixelAverage(x0, y0, x1, y1)
               + ps.getNonZeroCount(x0, y0, x1, y1)
               + ps.getNonZeroAverage(x0, y0, x1, y1);
    });
    return result;
}
