#ifndef RULES_FACTORY_HPP
#define RULES_FACTORY_HPP

#include <string>
#include "rules/Initialization/Initialization.hpp"
#include "rules/Neighbourhood/Neighbourhood.hpp"
#include "rules/Pivoting/Improvement.hpp"

struct RulesFactory {
    static Initialization* getInitialization(std::string initialization,
        Instance& instance);
    static Improvement* getPivotingRule(std::string pivotingRule,
        Instance& instance);
    static Neighbourhood* getNeighbourhood(std::string neighbourhood,
        unsigned size);
    static Neighbourhood** getVNDNeighbourhood(std::string neighbourhood,
        unsigned size);
};

#endif // RULES_FACTORY_HPP
