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

project(bip66 C CXX)

set(BIP66_SRC bip66.cpp)

add_library(${PROJECT_NAME} SHARED STATIC ${BIP66_SRC})

set(BIP66_BUILD_INCLUDE_DIRS ${PROJECT_SOURCE_DIR})

include_directories(${BIP66_BUILD_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC ${BIP66_BUILD_INCLUDE_DIRS})
