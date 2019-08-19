cmake_minimum_required(VERSION 3.2.2)

project(bip66 C CXX)

set(BIP66_SRC bip66.cpp)

add_library(bip66 SHARED STATIC ${BIP66_SRC})

set(BIP66_BUILD_INCLUDE_DIRS ${PROJECT_SOURCE_DIR})

include_directories(${BIP66_BUILD_INCLUDE_DIRS})

target_include_directories(bip66 PUBLIC ${BIP66_BUILD_INCLUDE_DIRS})
