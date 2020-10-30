#!/bin/sh

git clone https://github.com/google/googletest
mkdir build
mkdir include
cd build
cmake ../googletest
make
cd ..
cp -r googletest/googletest/include/gtest include
cp -r googletest/googlemock/include/gmock include

