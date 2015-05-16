#ifndef TABU_SEARCH_HPP
#define TABU_SEARCH_HPP

#include "rules/Initialization/Initialization.hpp"
#include "rules/Neighbourhood/Neighbourhood.hpp"
#include "rules/Pivoting/Improvement.hpp"

/**
 * The Tabu Search idea is to permit worsening results during the search, while
 * avoiding cycles by using a list of already visited results. This list has a
 * dynamic size in order to adapt to the current situation of the search. Most
 * of the Tabu Search mechanisms are handled by the TabuImprovement class.
 *
 * @see rules/Pivoting/TabuImprovement
 */
class TabuSearch {
public:
    /**
     * The termination criteria is the average computation time it takes to
     * run a full VND multiplied by 100. For an instance of size 150 it
     * gives us 293.959 s.
     * FIXME multiplied by 100
     */
    static const int TERMINATION_150_X10 = 29;
    
    /**
     * For an instance of size 250, the termination criterion is the average
     * time to compute a full VND multiplied by 10. It gives us 317.525 s.
     */
    static const int TERMINATION_250_X10 = 318;
    
    TabuSearch(Instance& instance,
        Initialization& initialization,
        Improvement& improvement,
        Neighbourhood& neighbourhood);
    
    void run();
    
private:
    Instance& instance_;
    Initialization& initialization_;
    Improvement& improvement_;
    Neighbourhood& neighbourhood_;
    
    int getTerminationTime();
};

#endif // TABU_SEARCH_HPP
