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

if [ -n "$1" ]; then
  echo "Started benchmark on ${1} tests"
  ./toyScheduler "${1}"
else
  echo "Started benchmark on 500 tests"
  ./toyScheduler 500
fi
)