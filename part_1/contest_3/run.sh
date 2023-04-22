#!/bin/env bash

aarch64-linux-gnu-as -c $1
aarch64-linux-gnu-gcc -static -o test a.out
qemu-aarch64 -L $2 ./test; 

res=$?

if [ "$3" -eq 1 ]; then
    echo $res
fi