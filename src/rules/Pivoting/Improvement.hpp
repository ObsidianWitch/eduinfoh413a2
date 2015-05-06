#ifndef IMPROVEMENT
#define IMPROVEMENT

#include "rules/Neighbourhood/Neighbourhood.hpp"
#include "Instance.hpp"
#include "Permutation.hpp"

class Improvement {
public:
    Improvement(const Instance& instance) : instance_(instance) {}
    virtual ~Improvement() {}

    virtual Permutation improve(Permutation& p, Neighbourhood& n) = 0;
    
protected:
    const Instance& instance_;
};

#endif // IMPROVEMENT
