#!/usr/bin/env bash

mkdir -p ~/Arduino/libraries/BIP66/
mv ~/project/* ~/Arduino/libraries/BIP66

arduino-cli compile --output temp.bin -b esp32:esp32:esp32 ~/Arduino/libraries/BIP66/examples/BIP66/BIP66.ino --debug
