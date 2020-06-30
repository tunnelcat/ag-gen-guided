#!/usr/bin/env bash
dropdb ag_gen
createdb ag_gen
./db_manage.sh -d ag_gen
