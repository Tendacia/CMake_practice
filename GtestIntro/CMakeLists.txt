# CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(Gtest C CXX )

# using gtest
find_package(GTest)


add_executable(example_unittest example_unittest.cpp)
target_link_libraries(example_unittest GTest::gtest GTest::gtest_main)
