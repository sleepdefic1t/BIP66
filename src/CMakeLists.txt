cmake_minimum_required(VERSION 3.2)
project(BIP66 C CXX)

set(SOURCE_FILES
    bip66.cpp
)

add_library(${PROJECT_NAME} SHARED STATIC ${SOURCE_FILES})

set(bip66_build_include_dirs
    ${PROJECT_SOURCE_DIR}
)
include_directories(${bip66_build_include_dirs})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${bip66_build_include_dirs}
)
