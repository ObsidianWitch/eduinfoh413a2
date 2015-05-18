#/bin/bash

# ./script mode startInstance endInstance m o t r

./experiments.lua run 1 10 4 2 4 4 &
./experiments.lua run 11 20 4 2 4 4 &
./experiments.lua run 21 30 4 2 4 4 &
./experiments.lua run 31 39 4 2 4 4
