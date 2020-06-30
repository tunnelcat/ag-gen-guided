#!/usr/bin/env bash

./clear_db.sh
cd build
./ag_gen -n ../examples/1.nm -x ../examples/1.xp 24 96

