#!/usr/bin/env bash

./clear_db.sh
rm -r build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make ag_gen
./ag_gen -n ../examples/thesis_example.nm -x ../examples/thesis_example.xp 24 96 
