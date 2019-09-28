#!/usr/bin/env bash

# run desktop builds
mkdir build && cd build
cmake .. -DBUILD_BIP66_TESTS=ON
cmake --build .

# run tests
./test/bip66_tests
