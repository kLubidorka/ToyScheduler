#!/bin/bash

if [ -d build ]; then
  rm -r build
fi

mkdir build
(
cd build/
declare -a solutions=("greedy" "knapsack")
for i in "${solutions[@]}"
do
  mkdir "${i}Reports"
  mkdir "${i}Solutions"
done
mkdir "tests"
cmake ..
make
./toyScheduler
)