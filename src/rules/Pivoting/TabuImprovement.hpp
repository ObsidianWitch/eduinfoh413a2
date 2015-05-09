#ifndef TABU_IMPROVEMENT
#define TABU_IMPROVEMENT

#include <deque>
#include "Improvement.hpp"

/**
 * TODO
 */
class TabuImprovement : public Improvement {
public:
    static const unsigned MAX_TABU_QUEUE = 200; // FIXME
    
    TabuImprovement(const Instance& instance);
    
    Permutation improve(Permutation& p, Neighbourhood& n);

private:
    std::deque<Permutation> tabuQueue;
    
    /**
     * Adds the given the given Permutation p to the tabuQueue. If the queue
     * contains MAX_TABU_QUEUE elements, push the new element at the beginning
     * of the queue, and pop the oldest one.
     */
    void updateTabuQueue(Permutation& p);
};

#endif // BEST_INFERIOR_IMPROVEMENT
