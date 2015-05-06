#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Instance.hpp"
#include "Permutation.hpp"
#include "rules/Initialization/CWInitialization.hpp"

int main() {
    Instance instance("../instances/test3");
    Permutation p1(instance.size());
    std::cout << "instance matrix" << std::endl
              << instance << std::endl
              << instance.evaluate(p1) << std::endl
              << std::endl;
    
    CWInitialization init(instance);
    Permutation p2 = init.generateInitialization();
    std::cout << "instance matrix with rows permuted"  << std::endl
              << instance << std::endl
              << instance.evaluate(p2) << std::endl;
    
    return EXIT_SUCCESS;
}
