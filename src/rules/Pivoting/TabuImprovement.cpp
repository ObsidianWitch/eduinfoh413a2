#include <algorithm>

#include "TabuImprovement.hpp"

TabuImprovement::TabuImprovement(const Instance& instance) :
    Improvement(instance),
    tabuQueue()
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
                tabuQueue.begin(), tabuQueue.end(), newP
            ) != tabuQueue.end();

            if (!isNewPTabu) {
                bestP = newP;
            }
        }

        n.next();
    }

    updateTabuQueue(bestP);

    return bestP;
}

/**
 * Adds the given Permutation p to the tabuQueue. If the queue
 * contains MAX_TABU_QUEUE elements, push the new element at the beginning
 * of the queue, and pop the oldest one.
 */
void TabuImprovement::updateTabuQueue(Permutation& p) {
    tabuQueue.push_front(p);
    if (tabuQueue.size() > MAX_TABU_QUEUE) {
        tabuQueue.pop_back();
    }
}
