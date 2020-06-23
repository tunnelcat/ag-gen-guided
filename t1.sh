#!/usr/bin/env bash

./db_manage.sh -d ag_gen
cd build
./ag_gen -n ../examples/1.nm -x ../examples/1.xp 4 64

