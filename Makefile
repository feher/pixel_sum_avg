CC := g++
OPTIONS := -O2 -std=c++17 -Wall -Wextra -Wpedantic -Wno-unused-variable
TEST_COMMON_SRC := test/TestHelper.cpp PixelSum.cpp

.PHONY: all test clean

all: mk_build_dir test

mk_build_dir:
	mkdir -p build

test: test/TestHelper.cpp \
	  test/TestHelper.hpp \
	  PixelSum.cpp \
	  PixelSum.hpp \
	  test/PixelSumTest_getPixelSum.cpp
	${CC} ${OPTIONS} -o build/PixelSumTest_getPixelSum \
	                    ${TEST_COMMON_SRC} \
                        test/PixelSumTest_getPixelSum.cpp
	${CC} ${OPTIONS} -o build/PixelSumTest_getPixelAverage \
	                    ${TEST_COMMON_SRC} \
                        test/PixelSumTest_getPixelAverage.cpp
	${CC} ${OPTIONS} -o build/PixelSumTest_getNonZeroCount \
	                    ${TEST_COMMON_SRC} \
                        test/PixelSumTest_getNonZeroCount.cpp
	${CC} ${OPTIONS} -o build/PixelSumTest_getNonZeroAverage \
	                    ${TEST_COMMON_SRC} \
                        test/PixelSumTest_getNonZeroAverage.cpp
	${CC} ${OPTIONS} -o build/PixelSumTest_perfTest \
	                    ${TEST_COMMON_SRC} \
                        test/PixelSumTest_perfTest.cpp
	${CC} ${OPTIONS} -o build/PixelSumTest_stressTest \
	                    ${TEST_COMMON_SRC} \
                        test/PixelSumTest_stressTest.cpp

clean:
	rm -rf ./build
