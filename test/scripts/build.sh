#!/bin/bash

# Build the test project
cmake -S ".." -B "../build"
cmake --build "../build"
cmake --build "../build" --target test