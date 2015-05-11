% H413 - A2

# Termination criterion

"As termination criterion, for each instance use the average computation time it
takes to run a full VND (implemented in the previous exercise) on the same
instance size and then multiply this time by 1000 (to allow for long enough runs
of the SLS algorithms)."

~~~
> grep -i _150 vnd_tie | awk '{ sum += $5; n++ } END { print sum/n }'
2.93959
> grep -i _250 vnd_tie | awk '{ sum += $5; n++ } END { print sum/n }'
31.7525

experiment    time_average (s)  *10      *100     *1000
vnd_tie_150   2.93959           29.3959  293.959  2939.59
vnd_tie_250   31.7525           317.525  3175.25  31752.5
~~~

<!-- TODO test
 - time_average, *10 and *100 with 150*150 instances
 - time_average and *10 with 250*250 instances
 -->

# Simple

## Tabu Search

~~~
s = init();
while (!termination_criterion) {
    n = set of non-tabu neighbours of s
    /* non-tabu neighbours: maintain a simple queue of permutations?
     * only keep a limited history, for example 10 permutations.*/
    s' = best_improve(n); // choose best neighbouring candidate solution s'
                          // in n, altouhgh it may be worse than current one
    update tabu attributes based on s' // add tabu solutions?
    s = s'
}
~~~

dynamic tabu search: p.482
The Reactive Tabu Search, ROBERTO BATTITI, GIAMPIETRO TECCHIOLLI

## Dynasearch

<!-- TODO -->

# Hybrid

## Iterated Local Search

<!-- TODO -->

## GRASP

<!-- TODO -->

# Population-based

## Ant Colony Optimisation

<!-- TODO -->

ACO <- ACS <- SAM <- SB-SAM
