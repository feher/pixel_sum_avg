#include <iostream>
#include <memory>
#include <cstddef>
#include <cstdlib>

#include "TestHelper.hpp"
#include "../PixelSum.hpp"

void test_getPixelAverage_entireBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelAverage(0, 0, width - 1, height - 1);
    TEST_ASSERT_EQ(result, (0 + 1 + 2 + 3 + 4) * 2 * height / static_cast<double>(width * height));
}

void test_getPixelAverage_leftTop() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelAverage(0, 0, 2, 2);
    TEST_ASSERT_EQ(result, (0 + 1 + 2) * 3 / static_cast<double>(3 * 3));
}

void test_getPixelAverage_rightTop() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelAverage(7, 0, 9, 2);
    TEST_ASSERT_EQ(result, (2 + 3 + 4) * 3 / static_cast<double>(3 * 3));
}

void test_getPixelAverage_leftBottom() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelAverage(0, 7, 2, 9);
    TEST_ASSERT_EQ(result, (0 + 1 + 2) * 3 / static_cast<double>(3 * 3));
}

void test_getPixelAverage_rightBottom() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelAverage(7, 7, 9, 9);
    TEST_ASSERT_EQ(result, (2 + 3 + 4) * 3 / static_cast<double>(3 * 3));
}

void test_getPixelAverage_entireBuffer_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = -100;
    const auto y0 = -100;
    const auto x1 = width + 100;
    const auto y1 = height + 100;
    const auto w = x1 - x0 + 1;
    const auto h = y1 - y0 + 1;
    const auto result = ps.getPixelAverage(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, (0 + 1 + 2 + 3 + 4) * 2 * height / static_cast<double>(w * h));
}

void test_getPixelAverage_leftTop_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = -5;
    const auto y0 = -5;
    const auto x1 = 2;
    const auto y1 = 2;
    const auto w = x1 - x0 + 1;
    const auto h = y1 - y0 + 1;
    const auto result = ps.getPixelAverage(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, (0 + 1 + 2) * 3 / static_cast<double>(w * h));
}

void test_getPixelAverage_rightTop_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = 7;
    const auto y0 = -100;
    const auto x1 = 100;
    const auto y1 = 2;
    const auto w = x1 - x0 + 1;
    const auto h = y1 - y0 + 1;
    const auto result = ps.getPixelAverage(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, (2 + 3 + 4) * 3 / static_cast<double>(w * h));
}

void test_getPixelAverage_leftBottom_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = -100;
    const auto y0 = 7;
    const auto x1 = 2;
    const auto y1 = 100;
    const auto w = x1 - x0 + 1;
    const auto h = y1 - y0 + 1;
    const auto result = ps.getPixelAverage(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, (0 + 1 + 2) * 3 / static_cast<double>(w * h));
}

void test_getPixelAverage_rightBottom_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = 7;
    const auto y0 = 7;
    const auto x1 = width + 100;
    const auto y1 = height + 100;
    const auto w = x1 - x0 + 1;
    const auto h = y1 - y0 + 1;
    const auto result = ps.getPixelAverage(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, (2 + 3 + 4) * 3 / static_cast<double>(w * h));
}

void test_getPixelAverage_reorderCoordinates() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = 2;
    const auto y0 = 2;
    const auto x1 = 0;
    const auto y1 = 0;
    const auto w = x0 - x1 + 1;
    const auto h = y0 - y1 + 1;
    const auto result = ps.getPixelAverage(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, (0 + 1 + 2) * 3 / static_cast<double>(w * h));
}

void test_getPixelAverage_bufferCanMeModified() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{1, 2, 3, 4, 5});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto resultA = ps.getPixelAverage(0, 0, 0, 0);
    ++buffer[0];
    const auto resultB = ps.getPixelAverage(0, 0, 0, 0);

    TEST_ASSERT_EQ(resultA, resultB);
}

void test_getPixelAverage_exampleTest() {
    const auto width = 3;
    const auto height = 2;
    const auto buffer = std::vector<unsigned char>{0, 4, 0, 2, 1, 0};
    const auto ps = PixelSum{buffer.data(), width, height};
    const auto result = ps.getPixelAverage(0, 0, 2, 1);
    TEST_ASSERT_EQ(result, (4 + 2 + 1) / static_cast<double>(width * height));
}

int main() {
    test_getPixelAverage_entireBuffer();
    test_getPixelAverage_leftTop();
    test_getPixelAverage_rightTop();
    test_getPixelAverage_leftBottom();
    test_getPixelAverage_rightBottom();

    test_getPixelAverage_entireBuffer_extendsBuffer();
    test_getPixelAverage_leftTop_extendsBuffer();
    test_getPixelAverage_rightTop_extendsBuffer();
    test_getPixelAverage_leftBottom_extendsBuffer();
    test_getPixelAverage_rightBottom_extendsBuffer();

    test_getPixelAverage_reorderCoordinates();
    test_getPixelAverage_bufferCanMeModified();

    test_getPixelAverage_exampleTest();
}
