#include <iostream>
#include <memory>
#include <cstddef>
#include <cstdlib>

#include "TestHelper.hpp"
#include "../PixelSum.hpp"

void test_getNonZeroCount_entireBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroCount(0, 0, width - 1, height - 1);
    TEST_ASSERT_EQ(result, 3 * 2 * height);
}

void test_getNonZeroCount_leftTop() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroCount(0, 0, 2, 2);
    TEST_ASSERT_EQ(result, 2 * 3);
}

void test_getNonZeroCount_rightTop() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroCount(7, 0, 9, 2);
    TEST_ASSERT_EQ(result, 2 * 3);
}

void test_getNonZeroCount_leftBottom() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroCount(0, 7, 2, 9);
    TEST_ASSERT_EQ(result, 2 * 3);
}

void test_getNonZeroCount_rightBottom() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getNonZeroCount(7, 7, 9, 9);
    TEST_ASSERT_EQ(result, 2 * 3);
}

void test_getNonZeroCount_entireBuffer_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = -100;
    const auto y0 = -100;
    const auto x1 = width + 100;
    const auto y1 = height + 100;
    const auto result = ps.getNonZeroCount(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, 3 * 2 * height);
}

void test_getNonZeroCount_leftTop_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = -5;
    const auto y0 = -5;
    const auto x1 = 2;
    const auto y1 = 2;
    const auto result = ps.getNonZeroCount(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, 2 * 3);
}

void test_getNonZeroCount_rightTop_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = 7;
    const auto y0 = -100;
    const auto x1 = 100;
    const auto y1 = 2;
    const auto result = ps.getNonZeroCount(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, 2 * 3);
}

void test_getNonZeroCount_leftBottom_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = -100;
    const auto y0 = 7;
    const auto x1 = 2;
    const auto y1 = 100;
    const auto result = ps.getNonZeroCount(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, 2 * 3);
}

void test_getNonZeroCount_rightBottom_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = 7;
    const auto y0 = 7;
    const auto x1 = width + 100;
    const auto y1 = height + 100;
    const auto result = ps.getNonZeroCount(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, 2 * 3);
}

void test_getNonZeroCount_reorderCoordinates() {
    const auto width = 10;
    const auto height = 10;
    auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    auto ps = PixelSum{buffer.get(), width, height};

    const auto x0 = 2;
    const auto y0 = 2;
    const auto x1 = 0;
    const auto y1 = 0;
    const auto result = ps.getNonZeroCount(x0, y0, x1, y1);
    TEST_ASSERT_EQ(result, 2 * 3);
}

void test_getNonZeroCount_bufferCanMeModified() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 0, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto resultA = ps.getNonZeroCount(0, 0, 0, 0);
    ++buffer[0];
    const auto resultB = ps.getNonZeroCount(0, 0, 0, 0);

    TEST_ASSERT_EQ(resultA, resultB);
}

void test_getNonZeroCount_exampleTest() {
    const auto width = 3;
    const auto height = 2;
    const auto buffer = std::vector<unsigned char>{0, 4, 0, 2, 1, 0};
    const auto ps = PixelSum{buffer.data(), width, height};
    const auto result = ps.getNonZeroCount(0, 0, width - 1, height - 1);
    TEST_ASSERT_EQ(result, 3);
}

int main() {
    test_getNonZeroCount_entireBuffer();
    test_getNonZeroCount_leftTop();
    test_getNonZeroCount_rightTop();
    test_getNonZeroCount_leftBottom();
    test_getNonZeroCount_rightBottom();

    test_getNonZeroCount_entireBuffer_extendsBuffer();
    test_getNonZeroCount_leftTop_extendsBuffer();
    test_getNonZeroCount_rightTop_extendsBuffer();
    test_getNonZeroCount_leftBottom_extendsBuffer();

    test_getNonZeroCount_reorderCoordinates();
    test_getNonZeroCount_bufferCanMeModified();

    test_getNonZeroCount_exampleTest();
}
