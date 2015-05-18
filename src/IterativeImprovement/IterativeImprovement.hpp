#ifndef ITERATIVE_IMPROVEMENT_HPP
#define ITERATIVE_IMPROVEMENT_HPP

#include "rules/Initialization/Initialization.hpp"
#include "rules/Neighbourhood/Neighbourhood.hpp"
#include "rules/Pivoting/Improvement.hpp"

/**
 * Try to find a good solution to the LOP problem by using different rules
 * (Initialization, Improvement and Neighbourhood).
 */
class IterativeImprovement {
public:
    IterativeImprovement(Instance& instance_, Initialization& initialization,
        Improvement& improvement, Neighbourhood& Neighbourhood);
    
    void run();

private:
    Instance& instance_;
    Initialization& initialization_;
    Improvement& improvement_;
    Neighbourhood& neighbourhood_;
};

#endif // ITERATIVE_IMPROVEMENT_HPP
