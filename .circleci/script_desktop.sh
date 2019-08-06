#!/usr/bin/env bash

# run desktop builds
cmake .
cmake --build .

# run Gtest
./test/BIP66-tests
