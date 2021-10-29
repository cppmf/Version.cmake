#!/bin/bash

# go to the root directory
cd ..

# Build the test project
cmake -S "test" -B "build/test"
cmake --build "build/test"
cmake --build "build/test" --target test