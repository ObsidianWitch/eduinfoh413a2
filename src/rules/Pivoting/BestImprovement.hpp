#ifndef BEST_IMPROVEMENT
#define BEST_IMPROVEMENT

#include "Improvement.hpp"

class BestImprovement : public Improvement {
public:
    BestImprovement(const Instance& instance);
    
    Permutation improve(Permutation& p, Neighbourhood& n);
};

#endif // BEST_IMPROVEMENT
