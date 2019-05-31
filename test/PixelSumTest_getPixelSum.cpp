#include <iostream>
#include <memory>
#include <cstddef>
#include <cstdlib>

#include "TestHelper.hpp"
#include "../PixelSum.hpp"

void test_getPixelSum_entireBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(0, 0, width - 1, height - 1);
    TEST_ASSERT_EQ(result, (0 + 1 + 2 + 3 + 4) * 2 * height);
}

void test_getPixelSum_leftTop() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(0, 0, 2, 2);
    TEST_ASSERT_EQ(result, (0 + 1 + 2) * 3);
}

void test_getPixelSum_rightTop() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(7, 0, 9, 2);
    TEST_ASSERT_EQ(result, (2 + 3 + 4) * 3);
}

void test_getPixelSum_leftBottom() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(0, 7, 2, 9);
    TEST_ASSERT_EQ(result, (0 + 1 + 2) * 3);
}

void test_getPixelSum_rightBottom() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(7, 7, 9, 9);
    TEST_ASSERT_EQ(result, (2 + 3 + 4) * 3);
}

void test_getPixelSum_entireBuffer_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(-100, -100, width + 100, height + 100);
    TEST_ASSERT_EQ(result, (0 + 1 + 2 + 3 + 4) * 2 * height);
}

void test_getPixelSum_leftTop_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(-5, -5, 2, 2);
    TEST_ASSERT_EQ(result, (0 + 1 + 2) * 3);
}

void test_getPixelSum_rightTop_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(7,   -100, 100,   2);
    TEST_ASSERT_EQ(result, (2 + 3 + 4) * 3);
}

void test_getPixelSum_leftBottom_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(-100, 7,    2,     100);
    TEST_ASSERT_EQ(result, (0 + 1 + 2) * 3);
}

void test_getPixelSum_rightBottom_extendsBuffer() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(7, 7, width + 100, height + 100);
    TEST_ASSERT_EQ(result, (2 + 3 + 4) * 3);
}

void test_getPixelSum_reorderCoordinates() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto result = ps.getPixelSum(2, 2, 0, 0);
    TEST_ASSERT_EQ(result, (0 + 1 + 2) * 3);
}

void test_getPixelSum_bufferCanMeModified() {
    const auto width = 10;
    const auto height = 10;
    const auto buffer = makeTestBuffer(width, height, std::vector<unsigned char>{0, 1, 2, 3, 4});
    const auto ps = PixelSum{buffer.get(), width, height};

    const auto resultA = ps.getPixelSum(0, 0, 0, 0);
    ++buffer[0];
    const auto resultB = ps.getPixelSum(0, 0, 0, 0);

    TEST_ASSERT_EQ(resultA, resultB);
}

void test_getPixelSum_exampleTest() {
    const auto width = 3;
    const auto height = 2;
    const auto buffer = std::vector<unsigned char>{0, 4, 0, 2, 1, 0};
    const auto ps = PixelSum{buffer.data(), width, height};
    const auto result = ps.getPixelSum(0, 0, 2, 1);
    TEST_ASSERT_EQ(result, 4 + 2 + 1);
}

int main() {
    test_getPixelSum_entireBuffer();
    test_getPixelSum_leftTop();
    test_getPixelSum_rightTop();
    test_getPixelSum_leftBottom();
    test_getPixelSum_rightBottom();

    test_getPixelSum_entireBuffer_extendsBuffer();
    test_getPixelSum_leftTop_extendsBuffer();
    test_getPixelSum_rightTop_extendsBuffer();
    test_getPixelSum_leftBottom_extendsBuffer();
    test_getPixelSum_rightBottom_extendsBuffer();

    test_getPixelSum_reorderCoordinates();
    test_getPixelSum_bufferCanMeModified();

    test_getPixelSum_exampleTest();
}
