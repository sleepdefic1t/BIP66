#!/usr/bin/env bash

# run desktop builds
mkdir build
cd build
cmake ..
cmake --build .

# run Gtest
./test/bip66_tests
