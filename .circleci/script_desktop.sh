#!/usr/bin/env bash

# run desktop builds
mkdir build
cd build
cmake .. -DUNIT_TEST
cmake --build .

# run Gtest
./test/bip66_tests
