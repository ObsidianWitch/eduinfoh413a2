#ifndef FIRST_IMPROVEMENT
#define FIRST_IMPROVEMENT

#include "Improvement.hpp"

/**
 * At a specific step of an algorithm with a given Instance, Permutation and
 * score, the FirstImprovement rules tries to find the first Permutation in the
 * given Neighbourhood which improves the instance's score.
 */
class FirstImprovement : public Improvement {
public:
    FirstImprovement(const Instance& instance);

    Permutation improve(Permutation& p, Neighbourhood& n);
};

#endif // FIRST_IMPROVEMENT
