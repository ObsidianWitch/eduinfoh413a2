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
    static const unsigned MAX_TABU_QUEUE_INIT = 8; // FIXME
    static const unsigned MAX_STEPS_NO_ELITE = 8; // FIXME
    
    TabuImprovement(const Instance& instance);
    
    Permutation improve(Permutation& p, Neighbourhood& n);

private:
    std::deque<Permutation> tabuQueue_;
    
    /**
     * Best score found so far by the Tabu Search.
     */
    int eliteScore_;
    
    /**
     * Number of search steps during which no elite solution was found.
     */
    unsigned stepsNoElite_;
    
    /**
     * Maximum number of elements the tabu queue can contain. Updated during
     * the search.
     *
     * @see updateElite()
     */
    unsigned maxTabuQueue_;
    
    Permutation stepTabuSearch(Permutation& p, Neighbourhood& n);
    bool checkRepetitions(Permutation& p, Permutation& newP);
    Permutation escape(Permutation& p);
    
    void updateElite(int currentScore);
    void updateTabuQueue(Permutation& p);
};

#endif // BEST_INFERIOR_IMPROVEMENT
