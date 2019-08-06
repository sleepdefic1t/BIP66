#!/usr/bin/env bash

# install PlatformIO
sudo pip install -U platformio

# update PlatformIO
platformio update

# install AUnit (2778) library
platformio lib -g install 2778
