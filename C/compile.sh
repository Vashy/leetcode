#!/usr/bin/env bash

BUILD_DIR=./build

set -x

cmake -DCMAKE_BUILD_TYPE=Debug -S . -G "Unix Makefiles" -B $BUILD_DIR

make --directory $BUILD_DIR
