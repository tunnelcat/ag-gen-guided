#!/usr/bin/env bash

./db_manage.sh -d ag_gen 
rm -r build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make ag_gen
./ag_gen -n ../examples/1.nm -x ../examples/1.xp 8 64
