#ifndef BEST_IMPROVEMENT
#define BEST_IMPROVEMENT

#include "Improvement.hpp"

/**
 * At a specific step of an algorithm with a given Instance, Permutation and
 * score, the BestImprovement rules tries to find the best Permutation in the
 * given Neighbourhood in order to improve the score.
 */
class BestImprovement : public Improvement {
public:
    BestImprovement(const Instance& instance);
    
    /**
     * The BestImprovement rule tries to find a Permutation which improves the
     * current instance score in comparison to the given Permutation p. It
     * iterates over the whole given Neighbourhood n in order to find the
     * permutation which increases the score the most (if it exists).
     * If no improvement can be found, the p Permutation given in parameter is
     * simply returned.
     */
    Permutation improve(Permutation& p, Neighbourhood& n);
};

#endif // BEST_IMPROVEMENT
