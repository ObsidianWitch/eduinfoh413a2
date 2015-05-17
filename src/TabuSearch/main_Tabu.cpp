#include <iostream>
#include <cstdlib>

#include "rules/Initialization/CWInitialization.hpp"
#include "rules/Pivoting/TabuImprovement.hpp"
#include "rules/Neighbourhood/InsertNeighbourhood.hpp"
#include "GlobalArgsTabu.hpp"
#include "TabuSearch.hpp"
#include "Instance.hpp"

int main(int argc, char *argv[]) {
    // Arguments handling
    GlobalArgsTabu g(argv[0]);
    
    if (argc < 11) {
        std::cout << "Missing argument" << std::endl;
        g.printHelp();
        return EXIT_FAILURE;
    }
    
    g.retrieve(argc, argv);

    // Algorithm dependencies
    Instance instance(g.filePath.c_str());
    CWInitialization initialization(instance);
    TabuImprovement improvement(instance, g);
    InsertNeighbourhood neighbourhood(instance.size());
    
    // Tabu Search
    TabuSearch ts(instance, initialization, improvement, neighbourhood);
    ts.run();
    
    return EXIT_SUCCESS;
}
