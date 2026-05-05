#!/bin/bash
BUILD_TYPE="Release"
if [ "$1" = "debug" ]; then
    BUILD_TYPE="Debug"
fi
cmake -B build -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build build
