# run desktop builds
cmake .
cmake --build .

# run Gtest
./test/BIP66_tests
