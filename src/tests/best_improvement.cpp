#include <iostream>
#include <cstdlib>
#include <cassert>

#include "rules/Neighbourhood/TransposeNeighbourhood.hpp"
#include "rules/Pivoting/BestImprovement.hpp"
#include "Permutation.hpp"
#include "Instance.hpp"

int main() {
    Instance instance("../instances/test2");
    Permutation p(instance.size());
    std::cout << "instance matrix" << std::endl
              << instance << std::endl;
    std::cout << "score: " << instance.evaluate(p) << std::endl << std::endl;
    
    TransposeNeighbourhood n(instance.size());
    
    BestImprovement bi(instance);
    Permutation improvedP = bi.improve(p, n);
    
    std::cout << "permutation instance matrix" << std::endl
              << instance.toStringMatrixPermutation(improvedP) << std::endl;
    std::cout << "score: " << instance.evaluate(improvedP) << std::endl
              << std::endl;
              
    improvedP = bi.improve(improvedP, n);

    std::cout << "permutation instance matrix" << std::endl
            << instance.toStringMatrixPermutation(improvedP) << std::endl;
    std::cout << "score: " << instance.evaluate(improvedP) << std::endl;

    return EXIT_SUCCESS;
}
