#!/usr/bin/env bash

./clear_db.sh
cd build
./ag_gen -n ../examples/cars3_rsh.nm -x ../examples/cars3_rsh.xp -g ../graph.dot 24 96
dot ../graph.dot -Tpng -o ../graph.png
