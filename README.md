# Heuristic Optimization 2nd assignment : Stochastic Local Search

## Description

Two Stochastic Local Search algorithms were implemented for the Linear Ordering
Problem.

* Tabu Search
* ??? (not implemented yet)

## Compilation

~~~
> mkdir out
> cd out
> cmake ..
> make tabu
~~~

## Run on one instance

### Tabu Search

~~~
Usage:./tabu <instance_file>

> ./tabu ../instances/N-be75tot_150
~~~

# Scripts

## Experiments

~~~
Usage: ./experiments mode startInstance endInstance m o t r

> ./experiments.lua conf 1 39
> ./experiments.lua run 1 39 4 2 4 4
~~~

## Parallel

~~~
> ./parallel_experiments.sh
~~~