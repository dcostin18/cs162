#!/bin/bash

if [[ -f $1 ]]; then
	touch wae.txt
	ls $1 | xargs echo -n >>wae.txt
	echo -n " " >>wae.txt
	aa="$(./fsmap.sh 'wc -w' $1)"
	echo -n $aa | grep -o [0-9]* | tr -d '\n' >>wae.txt
	echo -n " " >>wae.txt
	bb="$(./fsmap.sh 'wc -l' $1)"
	echo -n $bb | grep -o [0-9]* >>wae.txt
	cat wae.txt
	rm wae.txt
fi

if [[ -d $1 ]]; then
	./fsmap.sh ./"$0" $1
fi

