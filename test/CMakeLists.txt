
cmake_minimum_required(VERSION 3.2.2)

project(bip66_tests C CXX)

include(CTest)
enable_testing()

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../lib")

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/../extern/googletest
	"${CMAKE_CURRENT_SOURCE_DIR}/../build/extern/gtest"
)

set(BIP66_TEST_SRC bip66.cpp)

find_library(bip66_tests PUBLIC)

add_executable(bip66_tests ${BIP66_TEST_SRC})

target_link_libraries(bip66_tests bip66 gtest gtest_main)

add_test(NAME test COMMAND bip66_tests)
