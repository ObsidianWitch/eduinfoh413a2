#include <iostream>
#include <cstdlib>
#include <chrono>

#include "rules/Initialization/CWInitialization.hpp"
#include "rules/Pivoting/FirstImprovement.hpp"
#include "rules/RulesFactory.hpp"
#include "VariableNeighbourhoodDescent.hpp"
#include "GlobalArgsVND.hpp"
#include "Instance.hpp"

int main(int argc, char *argv[]) {
    using namespace std::chrono;
    
    // Arguments handling
    GlobalArgsVND g(argv[0]);
    
    if (argc < 5) {
        std::cout << "Missing argument" << std::endl;
        g.printHelp();
        return EXIT_FAILURE;
    }

    g.retrieve(argc, argv);
    g.checkArgs();
    
    // Algorithm dependencies
    Instance instance(g.filePath.c_str());
    CWInitialization initialization(instance);
    FirstImprovement improvement(instance);
    Neighbourhood** neighbourhoods = RulesFactory::getVNDNeighbourhood(
        g.neighbourhood, instance.size()
    );
    
    // VND algorithm
    VariableNeighbourhoodDescent vnd(instance, initialization, improvement,
        neighbourhoods);
    auto start = high_resolution_clock::now();
    vnd.run();
    duration<double> timeElapsed = high_resolution_clock::now() - start;
    std::cout << "Time elapsed: " << timeElapsed.count() << " s" << std::endl;
    
    // Memory handling
    for (unsigned i = 0 ; i < 3 ; i++) {
        delete neighbourhoods[i];
    }
    delete[] neighbourhoods;

    return EXIT_SUCCESS;
}
