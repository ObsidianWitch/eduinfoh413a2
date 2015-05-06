#ifndef CW_INITIALIZATION
#define CW_INITIALIZATION

#include "Initialization.hpp"

class CWInitialization : public Initialization  {
public:
    CWInitialization(Instance& instance);
    
    Permutation generateInitialization();
    
private:
    unsigned evaluateRows(const Permutation& permutation, unsigned step);
    long int evaluateRow(const Permutation& permutation, unsigned row,
        unsigned step);
};

#endif // CW_INITIALIZATION
