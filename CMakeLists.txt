
cmake_minimum_required(VERSION 3.2)

project(bip66)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(EXTERNAL_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/extern)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS
                    -D_SCL_SECURE_NO_WARNINGS
                    -DNOMINMAX)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

add_subdirectory(src)

option(UNIT_TEST "BIP66 tests disabled by default" OFF)

if(UNIT_TEST)
    add_subdirectory(test)
endif()
