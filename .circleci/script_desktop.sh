# run desktop builds
cmake .
cmake --build .

# run Gtest
cd ../../
./test/BIP66-tests
