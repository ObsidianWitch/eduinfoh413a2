#include "BestInferiorImprovement.hpp"

BestInferiorImprovement::BestInferiorImprovement(const Instance& instance) :
    Improvement(instance)
{}

Permutation BestInferiorImprovement::improve(Permutation& p, Neighbourhood& n) {
    if (p.score() == -1) {
        instance_.evaluate(p);
    }
    
    Permutation newP(instance_.size());
    long int bestScore = -1;
    
    n.start();
    while(n.isValid()) {
        long int newScore = instance_.evaluate(p, n);
        
        if (bestScore < newScore && p.score() != newScore) {
            newP = n.apply(p);
            newP.setScore(newScore);
            
            bestScore = newScore;
        }
        
        n.next();
    }
    
    return newP;
}
