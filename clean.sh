#!/bin/bash

# run both clean targets
cd ./kernel/ || exit 1
make clean
cd ../libc || exit 1
make clean
exit 0

