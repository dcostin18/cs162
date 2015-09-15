#!/bin/bash

if [[ -f $2 ]]; then
	$1 $2  
fi

if [[ -d $2 ]]; then
	for qax in "$2"/*; do
	./"$0" "$1" $qax
	done 
fi 

