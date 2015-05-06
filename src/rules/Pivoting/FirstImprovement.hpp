#ifndef FIRST_IMPROVEMENT
#define FIRST_IMPROVEMENT

#include "Improvement.hpp"

class FirstImprovement : public Improvement {
public:
    FirstImprovement(const Instance& instance);
    
    Permutation improve(Permutation& p, Neighbourhood& n);
};

#endif // FIRST_IMPROVEMENT
