#include "ExchangeNeighbourhood.hpp"

ExchangeNeighbourhood::ExchangeNeighbourhood(unsigned size) :
    Neighbourhood(size)
{}

void ExchangeNeighbourhood::start() {
    p_ = std::make_pair(0, 1);
}

bool ExchangeNeighbourhood::isValid() {
    return p_.first < size_ - 1;
}

void ExchangeNeighbourhood::next() {
    if (p_.second == size_ - 1) {
        p_.first++;
        p_.second = p_.first + 1;
    }
    else {
        p_.second++;
    }
}

Permutation ExchangeNeighbourhood::apply(const Permutation& p1) {
    Permutation p2 = p1;
    p2.permute(p_.first, p_.second);
    return p2;
}

long int ExchangeNeighbourhood::delta(const Matrix& matrix,
    const Permutation& oldP) const
{
    unsigned first = p_.first;
    unsigned second = p_.second;
    unsigned oldPfirst = oldP[first];
    unsigned oldPsecond = oldP[second];

    long int delta = matrix[oldPsecond][oldPfirst] - matrix[oldPfirst][oldPsecond];
    for (unsigned k = first + 1 ; k < second ; k++) {
        delta += matrix[oldPsecond][oldP[k]] - matrix[oldPfirst][oldP[k]];
        delta += matrix[oldP[k]][oldPfirst] - matrix[oldP[k]][oldPsecond];
    }

    return delta;
}
