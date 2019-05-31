#include <iostream>
#include <memory>
#include <cstddef>
#include <cstdlib>

#include "TestHelper.hpp"
#include "../PixelSum.hpp"

void test_getNonZeroAverage_entireBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroAverage(0, 0, width - 1, height - 1);
    const auto pixelSum = (1 + 2 + 4) * 2 * height;
    const auto nonZeroCount = 3 * 2 * height;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_leftTop() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroAverage(0, 0, 2, 2);
    const auto pixelSum = (1 + 2) * 3;
    const auto nonZeroCount = 2 * 3;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_rightTop() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroAverage(7, 0, 9, 2);
    const auto pixelSum = (2 + 4) * 3;
    const auto nonZeroCount = 2 * 3;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_leftBottom() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroAverage(0, 7, 2, 9);
    const auto pixelSum = (1 + 2) * 3;
    const auto nonZeroCount = 2 * 3;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_rightBottom() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroAverage(7, 7, 9, 9);
    const auto pixelSum = (2 + 4) * 3;
    const auto nonZeroCount = 2 * 3;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_entireBuffer_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = -100;
    const auto y0 = -100;
    const auto x1 = width + 100;
    const auto y1 = height + 100;
    const auto result = ps.getNonZeroAverage(x0, y0, x1, y1);
    const auto pixelSum = (1 + 2 + 4) * 2 * height;
    const auto nonZeroCount = 3 * 2 * height;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_leftTop_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = -5;
    const auto y0 = -5;
    const auto x1 = 2;
    const auto y1 = 2;
    const auto result = ps.getNonZeroAverage(x0, y0, x1, y1);
    const auto pixelSum = (1 + 2) * 3;
    const auto nonZeroCount = 2 * 3;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_rightTop_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = 7;
    const auto y0 = -100;
    const auto x1 = 100;
    const auto y1 = 2;
    const auto result = ps.getNonZeroAverage(x0, y0, x1, y1);
    const auto pixelSum = (2 + 4) * 3;
    const auto nonZeroCount = 2 * 3;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_leftBottom_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = -100;
    const auto y0 = 7;
    const auto x1 = 2;
    const auto y1 = 100;
    const auto result = ps.getNonZeroAverage(x0, y0, x1, y1);
    const auto pixelSum = (1 + 2) * 3;
    const auto nonZeroCount = 2 * 3;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_rightBottom_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = 7;
    const auto y0 = 7;
    const auto x1 = width + 100;
    const auto y1 = height + 100;
    const auto result = ps.getNonZeroAverage(x0, y0, x1, y1);
    const auto pixelSum = (2 + 4) * 3;
    const auto nonZeroCount = 2 * 3;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_reorderCoordinates() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = 2;
    const auto y0 = 2;
    const auto x1 = 0;
    const auto y1 = 0;
    const auto result = ps.getNonZeroAverage(x0, y0, x1, y1);
    const auto pixelSum = (1 + 2) * 3;
    const auto nonZeroCount = 2 * 3;
    TEST_ASSERT_EQ(result, pixelSum / static_cast<double>(nonZeroCount));
}

void test_getNonZeroAverage_bufferCanMeModified() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto resultA = ps.getNonZeroAverage(0, 0, 0, 0);
    ++buffer[0];
    const auto resultB = ps.getNonZeroAverage(0, 0, 0, 0);

    TEST_ASSERT_EQ(resultA, resultB);
}

void test_getNonZeroAverage_ZeroNotNaN() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroAverage(0, 0, 0, 0);
    TEST_ASSERT_EQ(result, 0);
}

void test_getNonZeroAverage_exampleTest() {
    const auto width = 3;
    const auto height = 2;
    const auto buffer = std::vector<unsigned char>{0, 4, 0, 2, 1, 0};
    const auto ps = PixelSum{buffer.data(), width, height};
    const auto result = ps.getNonZeroAverage(0, 0, width - 1, height - 1);
    TEST_ASSERT_EQ(result, (4 + 2 + 1) / 3.0);
}

int main() {
    test_getNonZeroAverage_entireBuffer();
    test_getNonZeroAverage_leftTop();
    test_getNonZeroAverage_rightTop();
    test_getNonZeroAverage_leftBottom();
    test_getNonZeroAverage_rightBottom();

    test_getNonZeroAverage_entireBuffer_extendsBuffer();
    test_getNonZeroAverage_leftTop_extendsBuffer();
    test_getNonZeroAverage_rightTop_extendsBuffer();
    test_getNonZeroAverage_leftBottom_extendsBuffer();
    test_getNonZeroAverage_rightBottom_extendsBuffer();

    test_getNonZeroAverage_reorderCoordinates();
    test_getNonZeroAverage_bufferCanMeModified();
    test_getNonZeroAverage_ZeroNotNaN();

    test_getNonZeroAverage_exampleTest();
}
