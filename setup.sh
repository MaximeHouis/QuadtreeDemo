#!/usr/bin/sh -ve

rm -rf build
mkdir build
cd build
cmake ..
make
