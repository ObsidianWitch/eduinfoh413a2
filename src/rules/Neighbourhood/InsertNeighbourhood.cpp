#include "InsertNeighbourhood.hpp"

InsertNeighbourhood::InsertNeighbourhood(unsigned size) :
    Neighbourhood(size)
{}

void InsertNeighbourhood::start() {
    p_ = std::make_pair(0, 1);
}

bool InsertNeighbourhood::isValid() {
    return p_.first < size_;
}

void InsertNeighbourhood::next() {
    // progress
    if (p_.second == size_ - 1) {
        p_.first++;
        p_.second = 0;
    }
    else {
        p_.second++;
    }
    
    // skip duplicates
    if ((p_.first == p_.second) || (p_.first == p_.second + 1)) {
        next();
    }
}

Permutation InsertNeighbourhood::apply(const Permutation& p1) {
    Permutation p2 = p1;
    p2.erase(p_.first);
    p2.insert(p_.second, p1[p_.first]);
    
    return p2;
}

long int InsertNeighbourhood::delta(const Matrix& matrix,
    const Permutation& oldP) const
{
    unsigned first = p_.first;
    unsigned second = p_.second;
    unsigned oldPfirst = oldP[first];
    
    long int delta = 0;
    if (first < second) {
        for (unsigned k = first + 1 ; k <= second ; k++) {
            delta += matrix[oldP[k]][oldPfirst] - matrix[oldPfirst][oldP[k]];
        }
    }
    else if (first > second) {
        for (unsigned k = second ; k <= first - 1 ; k++) {
            delta += matrix[oldPfirst][oldP[k]] - matrix[oldP[k]][oldPfirst];
        }
    }
    
    return delta;
}
