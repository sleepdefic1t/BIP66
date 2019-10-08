
cmake_minimum_required(VERSION 3.2)

project(bip66 C CXX)

# ------------------------------------------------------------------------------

add_library(${PROJECT_NAME} SHARED STATIC bip66.cpp)

set(BIP66_BUILD_INCLUDE_DIRS ${PROJECT_SOURCE_DIR})

include_directories(${BIP66_BUILD_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC ${BIP66_BUILD_INCLUDE_DIRS})

# ------------------------------------------------------------------------------
