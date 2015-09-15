#!/bin/bash

get_size () {
wc -c  < $1




}

export -f get_size

./fs_additive_fold.sh get_size $1
