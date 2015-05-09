#include "BestImprovement.hpp"

BestImprovement::BestImprovement(const Instance& instance) :
    Improvement(instance)
{}

/**
 * The BestImprovement rule tries to find a Permutation which improves the
 * current instance score in comparison to the given Permutation p. It
 * iterates over the whole given Neighbourhood n in order to find the
 * permutation which increases the score the most (if it exists).
 * If no improvement can be found, the p Permutation given in parameter is
 * simply returned.
 */
Permutation BestImprovement::improve(Permutation& p, Neighbourhood& n) {
    if (p.score() == -1) {
        instance_.evaluate(p);
    }
    
    Permutation p1 = p;
    
    n.start();
    while(n.isValid()) {
        
        long int scoreP2 = instance_.evaluate(p, n);
        
        if (p1.score() < scoreP2) {
            Permutation p2 = n.apply(p);
            p2.setScore(scoreP2);
            
            p1 = p2;
        }
        
        n.next();
    }
    
    return p1;
}
