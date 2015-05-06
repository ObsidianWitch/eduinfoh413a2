#include "CWInitialization.hpp"

CWInitialization::CWInitialization(Instance& instance) :
    Initialization(instance)
{}

Permutation CWInitialization::generateInitialization() {
    unsigned size = instance_.size();
    
    // Generate permutation of the rows
    Permutation rowsPermutation(size);
    
    for (unsigned step = 0 ; step < size ; step++) {
        unsigned bestRow = evaluateRows(rowsPermutation, step);
        rowsPermutation.permute(step, bestRow);
    }
    
    // Apply the permutation to the instance's rows
    instance_.permuteRows(rowsPermutation);
    
    // Generate a base permutation
    Permutation permutation(size);
    
    return permutation;
}

/**
 * Pick the best row at the specified step.
 */
unsigned CWInitialization::evaluateRows(const Permutation& permutation, unsigned step) {
    unsigned bestRow = step;
    long int bestRowScore = -1;
    
    for (unsigned row = step ; row < instance_.size() ; row++) {
        long int currentRowScore = evaluateRow(permutation, row, step);
        
        if (bestRowScore < currentRowScore) {
            bestRow = row;
            bestRowScore = currentRowScore;
        }
    }
    
    return bestRow;
}

long int CWInitialization::evaluateRow(const Permutation& permutation, unsigned row,
    unsigned step)
{
    long int score = 0;
    
    for (unsigned col = 1 + step ; col < instance_.size() ; col++) {
        score += instance_(permutation[row], col);
    }
    
    return score;
}
