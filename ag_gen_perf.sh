#!/usr/bin/env bash

PREFIX="$HOME/dev/ag_gen"
EXAMPLES="$PREFIX/examples"

NM=(
	$EXAMPLES/thesis_example.nm
	$EXAMPLES/thesis_example2.nm
	$EXAMPLES/SystemV12cda4.2.nm
)

XP=(
	$EXAMPLES/thesis_example.xp
	$EXAMPLES/thesis_example2.xp
	$EXAMPLES/cda4.1-SUPERSIMPLIFIED.xp
)

# Python
source activate agpy27
#cd $PREFIX

CSV="python_results.csv"
#CSV="rage_results.csv"

counter="0"

while [ $counter -lt $1 ]; do
TIMES=()
for (( i=0; i<${#NM[@]}; i++)) do
	result=$((/usr/bin/time python dev/ag_generator/hagGenerator.py \
		-nm ${NM[$i]} \
		-xp ${XP[$i]} \
		--no-viz-ag \
		--no-viz-states \
		--no-viz-matrix \
		--no-viz-paths \
		--no-viz-attacks \
		--state-graph 20 > /dev/null) 2>&1 \
		| perl -ne '/([0-9]+\.[0-9]+)user/ && print $1')
#	result=$($PREFIX/run.sh \
#		${NM[$i]} \
#		${XP[$i]} \
#		| perl -ne '/Total Time: ([0-9+\.[0-9]+)/ && print $1')
	TIMES+=("$result")
done

function join { local IFS="$1"; shift; echo "$*"; echo "$*" >> $CSV; }
join , ${TIMES[@]}

counter=$[$counter+1]
done

source deactivate
