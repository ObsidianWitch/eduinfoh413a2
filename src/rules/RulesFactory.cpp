#include "rules/Initialization/CWInitialization.hpp"
#include "rules/Initialization/RandomInitialization.hpp"
#include "rules/Neighbourhood/TransposeNeighbourhood.hpp"
#include "rules/Neighbourhood/ExchangeNeighbourhood.hpp"
#include "rules/Neighbourhood/InsertNeighbourhood.hpp"
#include "rules/Pivoting/BestImprovement.hpp"
#include "rules/Pivoting/FirstImprovement.hpp"
#include "RulesFactory.hpp"

Initialization* RulesFactory::getInitialization(std::string initialization,
    Instance& instance)
{
    if (initialization == "cw") {
        return new CWInitialization(instance);
    }
    else if (initialization == "random") {
        return new RandomInitialization(instance);
    }
    
    exit(EXIT_FAILURE);
}

Improvement* RulesFactory::getPivotingRule(std::string pivotingRule,
    Instance& instance)
{
    if (pivotingRule == "first") {
        return new FirstImprovement(instance);
    }
    else if (pivotingRule == "best") {
        return new BestImprovement(instance);
    }
    
    exit(EXIT_FAILURE);
}

Neighbourhood* RulesFactory::getNeighbourhood(std::string neighbourhood,
    unsigned size)
{
    if (neighbourhood == "transpose") {
        return new TransposeNeighbourhood(size);
    }
    else if (neighbourhood == "exchange") {
        return new ExchangeNeighbourhood(size);
    }
    else if (neighbourhood == "insert") {
        return new InsertNeighbourhood(size);
    }
    
    exit(EXIT_FAILURE);
}

Neighbourhood** RulesFactory::getVNDNeighbourhood(std::string neighbourhood,
    unsigned size)
{
    Neighbourhood** n = new Neighbourhood*[3];
    Neighbourhood* nt = new TransposeNeighbourhood(size);
    Neighbourhood* ne = new ExchangeNeighbourhood(size);
    Neighbourhood* ni = new InsertNeighbourhood(size);
    
    if (neighbourhood == "tei") {
        n[0] = nt; n[1] = ne; n[2] = ni;
        return n;
    }
    else if (neighbourhood == "tie") {
        n[0] = nt; n[1] = ni; n[2] = ne;
        return n;
    }
    
    exit(EXIT_FAILURE);
}
