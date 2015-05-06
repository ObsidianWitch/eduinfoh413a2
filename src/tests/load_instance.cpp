#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Instance.hpp"

int main() {
    Matrix testMatrix(5, MatrixRow(5));
    for (unsigned k = 0 ; k < 25 ; k++) {
        unsigned i = k / 5;
        unsigned j = k % 5;
        testMatrix[i][j] = k;
    }
    std::cout << "test matrix" << std::endl
              << testMatrix << std::endl << std::endl;
    
    Instance instance("../instances/test1");
    std::cout << "instance matrix" << std::endl
              << instance << std::endl << std::endl;
    
    assert(testMatrix == instance.matrix());
    
    std::cout << "instance totalSum: " << instance.totalSum() << std::endl;
    assert(instance.totalSum() == 300);
    
    return EXIT_SUCCESS;
}
