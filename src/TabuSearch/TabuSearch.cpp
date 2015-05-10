#include <chrono>
#include <assert.h>

#include "TabuSearch.hpp"

TabuSearch::TabuSearch(Instance& instance, Initialization& initialization,
    Improvement& improvement, Neighbourhood& neighbourhood) :
    instance_(instance), initialization_(initialization),
    improvement_(improvement), neighbourhood_(neighbourhood)
{}

/**
 * Runs the TabuSearch by using the rules given in the constructor.
 *
 * For the algorithm to work correctly, the Improvement rule should be the
 * TabuImprovement rule. This rule iterate over the Neighbourhood and allows
 * worsening results.
 *
 * Since worsening results are permitted, the best score is stored in a variable
 * during the search.
 *
 * The algorithm stops when the termination criterion is met: a
 * maximum computation time.
 *
 * @see rules/Pivoting/TabuImprovement
 * @see getTerminationTime()
 */
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
              
    Permutation bestP = p1;

    auto start = high_resolution_clock::now();
    duration<double> timeElapsed(0);
    while (timeElapsed.count() < terminationCriterion) {
        Permutation p2 = improvement_.improve(p1, neighbourhood_);

        std::cout << "p1.score:" << p1.score() << "\t" << "p2.score:"
            << p2.score()  << std::endl; // FIXME DEBUG
        
        // store the best permutation found during the search
        if (p2.score() > bestP.score()) {
            bestP = p2;
        }
        p1 = p2;
        

        timeElapsed = high_resolution_clock::now() - start;
    }
    std::cout << "Time elapsed: " << timeElapsed.count() << " s" << std::endl;

    long int finalScore = bestP.score();
    long int correctScore = instance_.evaluate(bestP);
    std::cout << "final solution (score: " << finalScore << "): "
              << bestP << std::endl
              << "best known score: " << instance_.bestScore() << std::endl;
    assert(finalScore == correctScore);
}

/**
 * Gets the termination time for the TabuSearch based on the instance size.
 * The termination time is based on the average computation time to run a full
 * VND.
 *
 * @return termination time, or -1 if the instance size cannot be handled yet.
 */
int TabuSearch::getTerminationTime() {
    if (instance_.size() == 150) {
        return TERMINATION_150_X10;
    }
    else if (instance_.size() == 250) {
        return TERMINATION_250_X10;
    }

    return -1;
}
