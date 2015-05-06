#ifndef VARIABLE_NEIGHBOURHOOD_DESCENT_HPP
#define VARIABLE_NEIGHBOURHOOD_DESCENT_HPP

#include "rules/Initialization/Initialization.hpp"
#include "rules/Neighbourhood/Neighbourhood.hpp"
#include "rules/Pivoting/Improvement.hpp"

class VariableNeighbourhoodDescent {
public:
    VariableNeighbourhoodDescent(Instance& instance,
        Initialization& initialization,
        Improvement& improvement,
        Neighbourhood** neighbourhoods);
    
    void run();

private:
    Instance& instance_;
    Initialization& initialization_;
    Improvement& improvement_;
    Neighbourhood** neighbourhoods_;
};

#endif // ITERATIVE_IMPROVEMENT_HPP
