#ifndef BEST_INFERIOR_IMPROVEMENT
#define BEST_INFERIOR_IMPROVEMENT

#include "Improvement.hpp"

/**
 * Select the best Permutation in the given Neighbourhood with the exclusion
 * of the current Permutation. This is done in order to permit inferior
 * Permutations compared to the current one.
 * FIXME this implementation always produces cycles between the best and best-1
 * result. In order to avoid that, implement a tabu queue instead of just
 * excluding the current Permutation.
 */
class BestInferiorImprovement : public Improvement {
public:
    BestInferiorImprovement(const Instance& instance);
    
    Permutation improve(Permutation& p, Neighbourhood& n);
};

#endif // BEST_INFERIOR_IMPROVEMENT
