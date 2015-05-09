#include <iostream>
#include <cstdlib>

#include "rules/Initialization/CWInitialization.hpp"
#include "rules/Pivoting/TabuImprovement.hpp"
#include "rules/Neighbourhood/InsertNeighbourhood.hpp"
#include "TabuSearch.hpp"
#include "Instance.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Missing argument" << std::endl
                  << "Usage:" << argv[0] << " <instance_file>" <<std::endl;
        return EXIT_FAILURE;
    }

    // Algorithm dependencies
    Instance instance(argv[1]);
    CWInitialization initialization(instance);
    TabuImprovement improvement(instance);
    InsertNeighbourhood neighbourhood(instance.size());
    
    // Tabu Search
    TabuSearch ts(instance, initialization, improvement, neighbourhood);
    ts.run();
    
    return EXIT_SUCCESS;
}
