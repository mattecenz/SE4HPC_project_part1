cmake_minimum_required(VERSION 3.10)
project(MatrixMultiplication)


include_directories(include)


add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test_multiplication_incorrect test/test_matrix_multiplication.cpp src/matrix_utils.cpp src/matrix_mult.cpp)
target_link_libraries(test_multiplication_incorrect gtest gtest_main ${CMAKE_SOURCE_DIR}/lib/libmatrix_multiplication_with_errors.a)

add_executable(test_multiplication_correct test/test_correct_matrix_multiplication.cpp src/matrix_mult.cpp)
target_link_libraries(test_multiplication_correct gtest gtest_main)


enable_testing()


include(GoogleTest)
gtest_discover_tests(test_multiplication_correct)
gtest_discover_tests(test_multiplication_incorrect)
