#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Instance.hpp"

int main() {
    Instance instance("../instances/test1");
    std::cout << "instance matrix" << std::endl
              << instance << std::endl << std::endl;

    Permutation p(instance.size());
    p.permute(0,1);
    
    std::cout << "permutation instance matrix" << std::endl
              << instance.toStringMatrixPermutation(p) << std::endl;
    
    return EXIT_SUCCESS;
}
