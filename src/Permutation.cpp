#include "Permutation.hpp"

Permutation::Permutation(unsigned size) :
    indices_(size)
{
    score_ = -1;
    size_ = size;
    fill();
}

void Permutation::fill() {
    for (unsigned i = 0 ; i < size() ; i++) {
        indices_[i] = i;
    }
}

void Permutation::permute(unsigned i1, unsigned i2) {
    unsigned tmp = indices_[i1];

    indices_[i1] = indices_[i2];
    indices_[i2] = tmp;
}

void Permutation::erase(unsigned i) {
    indices_.erase(indices_.begin() + i);
}

void Permutation::insert(unsigned i, unsigned element) {
    indices_.insert(indices_.begin() + i, element);
}

unsigned Permutation::operator[](unsigned i) const {
    return indices_[i];
}

unsigned& Permutation::operator[](unsigned i) {
    return indices_[i];
}

bool Permutation::operator ==(const Permutation& b) const {
    return (score_ == b.score());
}

unsigned Permutation::size() const { return size_; }

long int Permutation::score() const { return score_; }

void Permutation::setScore(long int score) {
    score_ = score;
}

std::ostream& operator<<(std::ostream& ostr, const Permutation& perm) {
    ostr << "(";

    for (unsigned i = 0 ; i < perm.size() ; i++) {
        if (i == perm.size() - 1) {
            ostr << perm[i];
        } else {
            ostr << perm[i] << ", ";
        }
    }

    ostr << ")" << std::endl;

    return ostr;
}
