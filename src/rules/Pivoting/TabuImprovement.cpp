#include <algorithm>

#include "TabuImprovement.hpp"

TabuImprovement::TabuImprovement(const Instance& instance) :
    Improvement(instance),
    tabuQueue_(),
    eliteScore_(-1),
    stepsNoElite_(0),
    maxTabuQueue_(MAX_TABU_QUEUE_INIT)
{}

/**
 * Improves or worsens the result (compared to the given Permutation p) by
 * selecting the best Permutation in the given Neighbourhood n. To avoid
 * revisiting Permutations, the tabuQueue is used.
 */
Permutation TabuImprovement::improve(Permutation& p, Neighbourhood& n) {
    if (p.score() == -1) {
        instance_.evaluate(p);
    }

    // create base permutation with score -1
    Permutation bestP(instance_.size());

    n.start();
    while(n.isValid()) {
        long int newScore = instance_.evaluate(p, n);

        if (bestP.score() < newScore) {
            Permutation newP = n.apply(p);
            newP.setScore(newScore);

            bool isNewPTabu = std::find(
                tabuQueue_.begin(), tabuQueue_.end(), newP
            ) != tabuQueue_.end();

            if (!isNewPTabu) {
                bestP = newP;
            }
        }

        n.next();
    }

    updateElite(bestP.score());
    updateTabuQueue(bestP);

    return bestP;
}

/**
 * If a new elite solution has been found, divides by 2 the maximum size of
 * the tabu queue and keep only the most recent part of the queue.
 * Else, if no elite solution has been found for MAX_STEPS_NO_ELITE, multiply
 * by 2 the tabu tenure.
 *
 * By decreasing the tabu tenure when an elite solution has been found helps
 * widening the search area.
 *
 * Increasing the tabu tenure when no elite solution has been found for a long
 * time helps avoiding cycles.
 */
void TabuImprovement::updateElite(int currentScore) {
    if (eliteScore_ < currentScore) {
        eliteScore_ = currentScore;
        
        if (maxTabuQueue_ > MAX_TABU_QUEUE_INIT) {
            if (tabuQueue_.size() > maxTabuQueue_/2) {
                auto middle = tabuQueue_.begin() + maxTabuQueue_/2;
                tabuQueue_ = std::deque<Permutation>(tabuQueue_.begin(), middle); // TODO check if correct behaviour
            }
            maxTabuQueue_ /= 2;
        }
        
        stepsNoElite_ = 0;

        std::cout << "elite (" << tabuQueue_.size() << "/" << maxTabuQueue_
                  << ") "; // FIXME DEBUG
    }
    else if (stepsNoElite_ == MAX_STEPS_NO_ELITE) {
        maxTabuQueue_ *= 2;
        stepsNoElite_ = 0;
        
        std::cout << "noElite (" << tabuQueue_.size() << "/" << maxTabuQueue_
                  << ") "; // FIXME DEBUG
    }
    else {
        stepsNoElite_++;
    }
}

/**
 * Adds the given Permutation p to the tabuQueue. If the queue
 * contains MAX_TABU_QUEUE elements, push the new element at the beginning
 * of the queue, and pop the oldest one.
 */
void TabuImprovement::updateTabuQueue(Permutation& p) {
    tabuQueue_.push_front(p);
    if (tabuQueue_.size() > maxTabuQueue_) {
        tabuQueue_.pop_back();
    }
}
