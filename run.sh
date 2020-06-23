#!/usr/bin/env bash

./db_manage.sh -d ag_gen 
./build/ag_gen $*
#dot -Tsvg -o ag.svg ag.dot

