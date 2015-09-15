#!/bin/bash

csum=0

fold_a () {


if [[ -f $2 ]]; then
	var=$($1 $2)
	#((csum += var))
	(( csum += var))
fi

if [[ -d $2 ]]; then
	for qux in "$2"/*; do
	fold_a "$1" $qux
	done
fi

}

fold_a $1 $2
echo $csum

