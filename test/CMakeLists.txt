
cmake_minimum_required(VERSION 3.2)

project(${PROJECT_NAME}_tests C CXX)

# ------------------------------------------------------------------------------
# Google Test
# ------------------------------------------------------------------------------

include(${CMAKE_SOURCE_DIR}/cmake/GTest.cmake)

# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Link BIP66 to the Test Libraries
# ------------------------------------------------------------------------------

find_library(bip66 PUBLIC)

add_executable(${PROJECT_NAME} bip66.cpp)

target_link_libraries(${PROJECT_NAME} bip66 gtest gtest_main)

# ------------------------------------------------------------------------------
