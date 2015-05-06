#include "BestImprovement.hpp"

BestImprovement::BestImprovement(const Instance& instance) :
    Improvement(instance)
{}

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
