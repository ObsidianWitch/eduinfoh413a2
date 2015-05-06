#ifndef INITIALIZATION_HPP
#define INITIALIZATION_HPP

#include "Instance.hpp"
#include "Permutation.hpp"

class Initialization {
public:
    Initialization(Instance& instance) : instance_(instance) {}
    virtual ~Initialization() {}
    
    virtual Permutation generateInitialization() = 0;
    
protected:
    Instance& instance_;
};

#endif // INITIALIZATION_HPP
