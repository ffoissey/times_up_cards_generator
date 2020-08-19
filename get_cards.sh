#!/bin/bash

make -j8 >/dev/null && make card
make clean
