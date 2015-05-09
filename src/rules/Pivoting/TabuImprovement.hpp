#ifndef TABU_IMPROVEMENT
#define TABU_IMPROVEMENT

#include <deque>
#include "Improvement.hpp"

/**
 * The TabuImprovement class selects the best scoring Permutation in the given
 * Neighbourhood. A Tabu list is kept to avoid selecting results already visited
 * recently. This list can keep at most MAX_TABU_QUEUE elements. The higher this
 * value is, the more we can avoid cycles, and the more we can find satisfying
 * results. However, the search is slower for larger lists.
 */
class TabuImprovement : public Improvement {
public:
    static const unsigned MAX_TABU_QUEUE = 200; // FIXME
    
    TabuImprovement(const Instance& instance);
    
    Permutation improve(Permutation& p, Neighbourhood& n);

private:
    std::deque<Permutation> tabuQueue;

    void updateTabuQueue(Permutation& p);
};

#endif // BEST_INFERIOR_IMPROVEMENT
