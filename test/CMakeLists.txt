cmake_minimum_required(VERSION 3.2)
project(BIP66_tests C CXX)

set(BUILD_GMOCK OFF FORCE)

add_subdirectory(lib/googletest)

find_library(BIP66 PUBLIC)

set(SOURCE_FILES
    src/iot/main.cpp
    src/bip66.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} BIP66 gtest gtest_main)
