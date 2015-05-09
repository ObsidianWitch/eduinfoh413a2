#ifndef TABU_SEARCH_HPP
#define TABU_SEARCH_HPP

#include "rules/Initialization/Initialization.hpp"
#include "rules/Neighbourhood/Neighbourhood.hpp"
#include "rules/Pivoting/Improvement.hpp"

class TabuSearch {
public:
    /**
     * The termination criteria is the average computation time it takes to
     * run a full VND multiplied by 10. For an instance of size 150 it
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
