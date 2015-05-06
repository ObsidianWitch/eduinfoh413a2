#include <assert.h>
#include "VariableNeighbourhoodDescent.hpp"

VariableNeighbourhoodDescent::VariableNeighbourhoodDescent(Instance& instance,
    Initialization& initialization,
    Improvement& improvement,
    Neighbourhood** neighbourhoods) :
    instance_(instance), initialization_(initialization),
    improvement_(improvement), neighbourhoods_(neighbourhoods)
{}

void VariableNeighbourhoodDescent::run() {
    Permutation p(instance_.size());
    std::cout << "instance size: " << instance_.size() << std::endl
              << "instance score: " << instance_.evaluate(p) << std::endl
              << "seed: " << instance_.totalSum() << std::endl;

    Permutation p1 = initialization_.generateInitialization();
    std::cout << "initial solution (score: " << instance_.evaluate(p1) << "): "
              << p1 << std::endl;

    int i = 0;
    while (i < 3) {
        Permutation p2 = improvement_.improve(p1, *neighbourhoods_[i]);
        
        if (p1 == p2) {
            i++;
        }
        else {
            /* DEBUG std::cout << "[" << i << "]" << p1.score() << " "
                      << p2.score() << std::endl;*/
            p1 = p2;
            i = 0;
        }
    }
    
    long int finalScore = p1.score();
    long int correctScore = instance_.evaluate(p1);
    std::cout << "final solution (score: " << finalScore << "): "
              << p1 << std::endl
              << "best known score: " << instance_.bestScore() << std::endl;
    assert(finalScore == correctScore);
}
