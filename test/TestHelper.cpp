#include <cstring>
#include <random>

#include "TestHelper.hpp"

std::unique_ptr<unsigned char[]> makeTestBuffer(int width, int height, const std::vector<unsigned char>& pattern) {
    auto buffer = std::unique_ptr<unsigned char[]>{new unsigned char[width * height]};
    const auto maxCount = width * height;
    for (auto i = 0; i < maxCount; i += pattern.size()) {
        const auto countRemaining = maxCount - i;
        const auto n = std::min(static_cast<int>(pattern.size()), countRemaining);
        std::memcpy(buffer.get() + i, pattern.data(), n);
    }
    return buffer;
}

std::unique_ptr<unsigned char[]> makeTestBuffer(int width, int height) {
    auto buffer = std::unique_ptr<unsigned char[]>{new unsigned char[width * height]};

    auto randDevice = std::random_device{};
    auto randEngine = std::mt19937{randDevice()};
    auto dist = std::uniform_int_distribution<int>{0, 255};

    for (auto i = 0; i < width * height; ++i) {
        buffer[i] = dist(randEngine);
    }
    return buffer;
}
