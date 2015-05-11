#include <functional>
#include "RandomInitialization.hpp"

RandomInitialization::RandomInitialization(Instance& instance) :
    Initialization(instance),
    randomEngine_(instance.totalSum()), size_(instance.size())
{}


Permutation RandomInitialization::generateInitialization() {
    std::uniform_int_distribution<unsigned> distribution(0, size_ - 1);
    Permutation randomPermutation(size_);

    for (unsigned i = 0 ; i < randomPermutation.size() ; i++) {
        unsigned randomIndex = distribution(randomEngine_);
        
        randomPermutation.permute(i, randomIndex);
    }
    
    return randomPermutation;
}
