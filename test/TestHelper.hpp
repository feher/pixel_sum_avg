#ifndef __TEST_HELPER_HPP__
#define __TEST_HELPER_HPP__

#include <memory>

#include "../PixelSum.hpp"

#define TEST_ASSERT_EQ(a, b) \
do { \
  const auto va = (a); \
  const auto vb = (b); \
  if (va != vb) { \
    std::cerr << "Failed: " << __func__ << ": " << #a << " != " << #b << ", " << va << " != " << vb << std::endl; \
    std::exit(1); \
  } \
} while (false)

/**
 * Creates a buffer of size (width * height). Fills the buffer with the given pattern of bytes.
 */
std::unique_ptr<unsigned char[]> makeTestBuffer(int width, int height, const std::vector<unsigned char>& pattern);

/**
 * Creates a buffer of size (width * height). Fills the buffer with random bytes.
 */
std::unique_ptr<unsigned char[]> makeTestBuffer(int width, int height);

#endif
