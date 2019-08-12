
cmake_minimum_required(VERSION 3.2)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
	message(FATAL_ERROR
		"\n=================================================\n"
		"ERROR: Out of Source Build attempted.\n"
		"You cannot build in a source directory (or any directory with a CMakeLists.txt file).\n"
		"Please use the build directory at root.\n"
		"e.g. 'mkdir build && cd build && cmake ../ && cmake --build .'\n"
		"You should also remove CMakeCache.txt and CMakeFiles.\n"
		"=================================================\n")
endif()

project(bip66_tests C CXX)

set(BUILD_GMOCK OFF FORCE)
include(CTest)
enable_testing()

add_subdirectory(
	${CMAKE_CURRENT_SOURCE_DIR}/../extern/googletest
	"${CMAKE_CURRENT_SOURCE_DIR}/../build/extern/gtest"
)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../lib")

set(BIP66_TEST_SRC
	# src/iot/main.cpp
	bip66.cpp
)

find_library(${PROJECT_NAME} PUBLIC)

add_executable(${PROJECT_NAME} ${BIP66_TEST_SRC})

target_link_libraries(${PROJECT_NAME} bip66 gtest gtest_main)

add_test(NAME test COMMAND bip66_tests)
