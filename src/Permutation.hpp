#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include <vector>
#include <iostream>

class Permutation {
public:
    Permutation(unsigned size);

    void fill();
    void permute(unsigned i1, unsigned i2);
    void erase(unsigned i);
    void insert(unsigned i, unsigned element);
    
    // Operators
    unsigned operator[](unsigned i) const;
    unsigned& operator[](unsigned i);
    bool operator ==(const Permutation& b) const;

    // Accessors
    unsigned size() const;
    long int score() const;
    void setScore(long int score);
    
private:
    std::vector<unsigned> indices_;
    unsigned size_;
    long int score_;
};

std::ostream& operator<<(std::ostream& ostr, const Permutation& perm);

#endif // PERMUTATION_HPP
