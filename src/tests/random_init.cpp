#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Instance.hpp"
#include "Permutation.hpp"
#include "rules/Initialization/RandomInitialization.hpp"

int main() {
    Instance instance("../instances/test1");
    RandomInitialization init(instance);
    Permutation p = init.generateInitialization();
    
    std::cout << p;
    
    return EXIT_SUCCESS;
}
