#include <chrono>
#include <assert.h>

#include "TabuSearch.hpp"

TabuSearch::TabuSearch(Instance& instance, Initialization& initialization,
    Improvement& improvement, Neighbourhood& neighbourhood) :
    instance_(instance), initialization_(initialization),
    improvement_(improvement), neighbourhood_(neighbourhood)
{}

void TabuSearch::run() {
    using namespace std::chrono;
    
    int terminationCriterion = getTerminationTime();
    assert(terminationCriterion != 0);

    Permutation p(instance_.size());
    std::cout << "instance size: " << instance_.size() << std::endl
              << "instance score: " << instance_.evaluate(p) << std::endl
              << "seed: " << instance_.totalSum() << std::endl;

    Permutation p1 = initialization_.generateInitialization();
    std::cout << "initial solution (score: " << instance_.evaluate(p1) << "): "
              << p1 << std::endl;


    auto start = high_resolution_clock::now();
    duration<double> timeElapsed(0);
    while (timeElapsed.count() < terminationCriterion) {
        Permutation p2 = improvement_.improve(p1, neighbourhood_);

        /* DEBUG std::cout << "p1.score:" << p1.score() << "\t" << "p2.score:"
            << p2.score()  << std::endl;*/
        
        p1 = p2;
        
        timeElapsed = high_resolution_clock::now() - start;
    }
    std::cout << "Time elapsed: " << timeElapsed.count() << " s" << std::endl;

    long int finalScore = p1.score();
    long int correctScore = instance_.evaluate(p1);
    std::cout << "final solution (score: " << finalScore << "): "
              << p1 << std::endl
              << "best known score: " << instance_.bestScore() << std::endl;
    assert(finalScore == correctScore);
}

/**
 * Get the termination time for the TabuSearch based on the instance size.
 * The termination time is based on the average computation time to run a full
 * VND.
 *
 * @return termination time, or -1 if the instance size cannot be handled yet.
 */
int TabuSearch::getTerminationTime() {
    if (instance_.size() == 150) {
        return TERMINATION_150_X100;
    }
    else if (instance_.size() == 250) {
        return TERMINATION_250_X10;
    }

    return -1;
}
