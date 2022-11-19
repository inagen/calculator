#!/bin/bash
cmake -S . -B build
cd build
make
mv calculator ../calculator
cd ../