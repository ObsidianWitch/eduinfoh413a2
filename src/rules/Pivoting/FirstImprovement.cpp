#include "FirstImprovement.hpp"

FirstImprovement::FirstImprovement(const Instance& instance) :
    Improvement(instance)
{}

/**
 * Finds the first Permutation in the Neighbourhood n which has
 * a better score than the given Permutation p for the current instance.
 */
Permutation FirstImprovement::improve(Permutation& p, Neighbourhood& n) {
    if (p.score() == -1) {
        instance_.evaluate(p);
    }
    
    n.start();
    while(n.isValid()) {

        long int scoreP2 = instance_.evaluate(p, n);

        if (p.score() < scoreP2) {
            Permutation p2 = n.apply(p);
            p2.setScore(scoreP2);
            
            return p2;
        }
        
        n.next();
    }
    
    return p;
}
