#!/usr/bin/env bash

# run desktop builds
mkdir build
cd build
cmake .. -DUNIT_TESTS=true
cmake --build .

# run Gtest
./test/bip66_tests
