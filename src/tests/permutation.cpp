#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Permutation.hpp"

int main() {
    Permutation p(10);
    std::cout << p;
    
    for (unsigned i = 0 ; i < 10 ; i++) {
        assert(p[i] == i);
    }
    std::cout << std::endl;
    
    p.permute(0, 2);
    std::cout << p;
    
    assert(p[0] == 2);
    assert(p[2] == 0);

    return EXIT_SUCCESS;
}
