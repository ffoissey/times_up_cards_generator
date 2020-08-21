#!/bin/bash

cat resources/list.txt | sort | uniq > resources/tmp.txt
cp resources/tmp.txt resources/list.txt
rm -f resources/tmp.txt
make -j8 >/dev/null && make card
make clean
