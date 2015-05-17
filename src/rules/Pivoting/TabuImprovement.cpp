#include <algorithm>

#include "TabuImprovement.hpp"
#include "Debug.hpp"

TabuImprovement::TabuImprovement(const Instance& instance) :
    Improvement(instance),
    tabuQueue_(),
    tabuTenure_(1),
    permutationOccurrences_(),
    frequentlyEncountered_(),
    ttIterationsNoModif(0),
    gen_(instance_.totalSum()),
    eliteP_(instance.size())
{}

/**
 * Improves or worsens the result (compared to the given Permutation p) by
 * selecting the best Permutation in the given Neighbourhood n. To avoid
 * revisiting Permutations, the tabuQueue is used.
 * If the search seems to be stuck in a cycle, the escape mechanism is
 * triggered.
 */
Permutation TabuImprovement::improve(Permutation& p, Neighbourhood& n) {
    Permutation newP = stepTabuSearch(p, n);

    if (checkRepetitions(newP)) {
        debug << "escape ";
        newP = escape(p);
    }

    debug << "(" << tabuTenure_ << "," << ttIterationsNoModif << ") ";

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

    updateTabuQueue(bestP);
    updateElite(bestP);

    return bestP;
}

/**
 * Checks whether there is a risk of the tabu search being stuck in a search
 * zone.
 *
 * A short term solution is to increase the tabu tenure. However, increasing
 * too much the tabu tenure may constrain the search zone. So, under some
 * conditions, the tabu tenure is occasionally decreased.
 *
 * If the short term solution is not sufficient, then checkRepetitions returns
 * true to indicate the Tabu Search seems to be stuck. In that case, other
 * solutions may be employed, such as escape mechanisms.
 *
 * @return Returns true if the search seems to be stuck, false otherwise.
 */
bool TabuImprovement::checkRepetitions(Permutation& newP) {
    auto searchNewP = permutationOccurrences_.find(newP.score());
    if (searchNewP != permutationOccurrences_.end()) {
        tabuTenure_ += TT_INC;
        ttIterationsNoModif = 0;

        // newP has been encountered again, increase the number of occurrences
        // in the hash table.
        searchNewP->second++;

        if (searchNewP->second > MAX_OCCURRENCES_FREQUENTLY_ENCOUNTERED) {
            // Insert newP in the set of frequently encountered Permutations (if
            // it is not already in there).
            frequentlyEncountered_.insert(newP.score());

            // If the number of frequently encountered candidate solutions
            // exceeds MAX_CANDIDATE_FREQUENTLY_ENCOUNTERED, return true;
            return frequentlyEncountered_.size() > MAX_CANDIDATE_TRIGGER_ESCAPE;
        }
    }
    else {
        ttIterationsNoModif++;

        // newP has been encountered for the first time, inserts it in the
        // hash table
        permutationOccurrences_.insert(
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
 * The escape mechanism is used to explore a new search zone.
 * Resets all variables linked to the reactive tabu search to their initial
 * values (e.g. tabu queue, tabu tenure).
 * The escape is achieved by a random number of step applied to the current
 * Permutation p.
 */
Permutation TabuImprovement::escape(Permutation& p) {
    // Resets all mechanisms linked to the Tabu Search
    tabuTenure_ = 1;
    ttIterationsNoModif = 0;
    tabuQueue_.clear();
    permutationOccurrences_.clear();
    frequentlyEncountered_.clear();

    // Escape from the current search region
    Permutation newP = p;

    std::uniform_int_distribution<> disRandSteps(2, MAX_RANDOM_STEPS_ESCAPE);
    std::uniform_int_distribution<> disIndex(0, instance_.size() - 1);

    unsigned nRandomSteps = disRandSteps(gen_);
    for (unsigned i = 0 ; i < nRandomSteps ; i++) {
        unsigned j = disIndex(gen_);
        unsigned k = disIndex(gen_);

        debug << " <->(" << j << "," << k <<") ";

        newP.permute(j, k);
        instance_.evaluate(newP);
        
        // Add each Permutation leading to the new search zone in the tabuQueue_
        // in order to avoid going back to the old search zone.
        updateTabuQueue(newP);
    }


    return newP;
}

/**
 * Adds the given Permutation p to the tabuQueue_. If the queue
 * contains more than tabuTenure_ elements, pop enough old elements to
 * satisfy the tabu tenure.
 */
void TabuImprovement::updateTabuQueue(Permutation& p) {
    tabuQueue_.push_front(p);
    while (tabuQueue_.size() > tabuTenure_) {
        tabuQueue_.pop_back();
    }
}

/**
 * Detect if the newly found Permutation is an elite Permutation. An elite
 * Permutation has the best score among the solutions found by the Tabu Search
 * thus far.
 * If a new elite Permutation has been found, divides by 2 the tabu tenure in
 * order to avoid restricting too much the search zone.
 */
void TabuImprovement::updateElite(Permutation& newP) {
    if (newP.score() > eliteP_.score()) {
        eliteP_ = newP;

        if (tabuTenure_ > 1) {
            tabuTenure_ /= 2;
        }

        debug << "elite ";
    }
}
