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
