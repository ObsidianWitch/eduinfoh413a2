#include <iostream>
#include <cstdlib>
#include <cassert>
#include "rules/Neighbourhood/TransposeNeighbourhood.hpp"
#include "rules/Neighbourhood/ExchangeNeighbourhood.hpp"
#include "rules/Neighbourhood/InsertNeighbourhood.hpp"
#include "Permutation.hpp"

void testTranspose() {
    Permutation p(4);
    TransposeNeighbourhood n(p.size());

    std::cout << "TransposeNeighbourhood" << std::endl;
    n.start();
    while (n.isValid()) {
        Permutation p2 = n.apply(p);
        std::cout << n << ": " << p2 << std::endl;
        n.next();
    }
    std::cout << std::endl;
}

void testExchange() {
    Permutation p(4);
    ExchangeNeighbourhood n(p.size());

    std::cout << "ExchangeNeighbourhood" << std::endl;
    n.start();
    while (n.isValid()) {
        Permutation p2 = n.apply(p);
        std::cout << n << ": " << p2 << std::endl;
        n.next();
    }
    std::cout << std::endl;
}

void testInsert() {
    Permutation p(4);
    InsertNeighbourhood n(p.size());

    std::cout << "InsertNeighbourhood" << std::endl;
    n.start();
    while (n.isValid()) {
        Permutation p2 = n.apply(p);
        std::cout << n << ": " << p2 << std::endl;
        n.next();
    }
    std::cout << std::endl;
}

int main() {
    testTranspose();
    testExchange();
    testInsert();
    
    return EXIT_SUCCESS;
}
