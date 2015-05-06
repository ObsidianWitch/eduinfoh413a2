#ifndef INSERT_NEIGHBOURHOOD_HPP
#define INSERT_NEIGHBOURHOOD_HPP

#include "Neighbourhood.hpp"

class InsertNeighbourhood : public Neighbourhood {
public:
    InsertNeighbourhood(unsigned size);
    
    void start();
    bool isValid();
    void next();
    Permutation apply(const Permutation& p1);
    long int delta(const Matrix& matrix, const Permutation& oldP) const;
};

#endif // INSERT_NEIGHBOURHOOD_HPP
