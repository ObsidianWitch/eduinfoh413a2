#include <algorithm>

#include "TabuImprovement.hpp"

TabuImprovement::TabuImprovement(const Instance& instance) :
    Improvement(instance),
    tabuQueue_(),
    tabuTenure_(1),
    permutationOccurences_(),
    frequentlyEncountered_(),
    ttIterationsNoModif(0)
{}

/**
 * Improves or worsens the result (compared to the given Permutation p) by
 * selecting the best Permutation in the given Neighbourhood n. To avoid
 * revisiting Permutations, the tabuQueue is used.
 * FIXME update doc
 */
Permutation TabuImprovement::improve(Permutation& p, Neighbourhood& n) {
    Permutation newP = stepTabuSearch(p, n);

    if (checkRepetitions(p, newP)) {
        std::cout << "escape "; // FIXME DEBUG
        newP = escape(p);
    }

    std::cout << "(" << tabuTenure_ << "," << ttIterationsNoModif
              << ") "; // FIXME DEBUG

    return newP;
}

/**
 * Retrieves the best non-tabu Permutation in the given Neighbourhood n.
 * After that, insert the new Permutation in the tabu queue.
 */
Permutation TabuImprovement::stepTabuSearch(Permutation& p, Neighbourhood& n) {
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
    
    if (bestP.score() == -1) {
        std::cout << "sokomadeda!" << std::endl;
        exit(EXIT_FAILURE);
    }

    updateTabuQueue(bestP);

    return bestP;
}

/**
 * Checks whether there is a risk of the tabu search being stuck in a search
 * zone.
 *
 * A short term solution is to increase the tabu tenure. However, increasing
 * too much the tabu tenure may also cause the tabu search to be stuck by
 * constraining the search zone. So, under some conditions, the tabu tenure
 * is occasionally decreased (see comments inside code).
 *
 * If the short term solution is not sufficient, then checkRepetitions returns
 * true to indicate the Tabu Search seems to be stuck. In that case, other
 * solutions may be employed, such as escape mechanisms.
 *
 * @return Returns true if the search seems to be stuck, false otherwise.
 */
bool TabuImprovement::checkRepetitions(Permutation& p, Permutation& newP) {
    auto searchNewP = permutationOccurences_.find(newP.score());
    if (searchNewP != permutationOccurences_.end()) {
        tabuTenure_ += TT_INC;
        ttIterationsNoModif = 0;

        // newP has been encountered again, increase the number of occurences
        // in the hash table.
        searchNewP->second++;

        if (searchNewP->second > MAX_OCCURENCES_FREQUENTLY_ENCOUNTERED) {
            // Insert newP in the set of frequently encountered Permutations (if
            // it is not already in there).
            frequentlyEncountered_.insert(newP.score());

            // If the number of frequently encountered candidate solutions
            // exceeds MAX_CANDIDATE_FREQUENTLY_ENCOUNTERED, return true;
            return frequentlyEncountered_.size() > MAX_CANDIDATE_FREQUENTLY_ENCOUNTERED;
        }
    }
    else {
        ttIterationsNoModif++;

        // newP has been encountered for the first time, inserts it in the
        // hash table
        permutationOccurences_.insert(
            std::make_pair(newP.score(), 1)
        );
    }

    // If the tabu tenure is only increased, it may constrain the search (the
    // largest the tabu list is, the less Permutations are allowed as
    // candidate solutions). So, if no change to the tabu tenure value has
    // happened for a sufficient number of iterations, decrease it.
    if (ttIterationsNoModif > TT_ITERATIONS_WO_MODIFICATION) {
        if (tabuTenure_ > 1) {
            tabuTenure_ -= TT_DEC;
        }
    }

    return false;
}

/**
 * TODO
 */
Permutation TabuImprovement::escape(Permutation& p) {
    // TODO
    return p; // FIXME temp
}

/**
 * Adds the given Permutation p to the tabuQueue. If the queue
 * contains more than tabuTenure_ elements, pop enough old elements to
 * satisfy the tabu tenure.
 */
void TabuImprovement::updateTabuQueue(Permutation& p) {
    tabuQueue_.push_front(p);
    while (tabuQueue_.size() > tabuTenure_) {
        tabuQueue_.pop_back();
    }
}
