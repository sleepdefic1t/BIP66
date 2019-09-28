
cmake_minimum_required(VERSION 3.2)

project(bip66_tests C CXX)

# ------------------------------------------------------------------------------
# Google Test
# ------------------------------------------------------------------------------

# clone submodules
execute_process(
	COMMAND git submodule update --init --recursive
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

option(BUILD_GMOCK OFF FORCE)
option(PACKAGE_TESTS OFF FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(../extern/googletest [EXCLUDE_FROM_ALL])

# ------------------------------------------------------------------------------

find_library(BIP66 PUBLIC)

add_executable(${PROJECT_NAME} bip66.cpp)
target_link_libraries(${PROJECT_NAME} BIP66 gtest gtest_main)
