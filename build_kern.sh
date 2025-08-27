#!/bin/bash

# build the kernel
cd ./kernel/ || exit 1
make all
exit 0
