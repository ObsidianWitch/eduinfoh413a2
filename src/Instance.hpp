#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <string>
#include <vector>
#include "Permutation.hpp"
#include "rules/Neighbourhood/Neighbourhood.hpp"

typedef std::vector<int> MatrixRow;
typedef std::vector<MatrixRow> Matrix;
typedef std::pair<unsigned, unsigned> Pair;

class Instance {
public:
    Instance(std::string filePath);
    
    void parseToMatrix();
    long int evaluate(Permutation& p) const;
    long int evaluate(Permutation& oldP, const Neighbourhood& n) const;
    void permuteRows(const Permutation& p);
    std::string toStringMatrixPermutation(const Permutation& p) const;
    static std::string toStringMatrixPermutation(const Matrix& matrix,
        const Permutation& p);
    
    int operator()(unsigned i, unsigned j) const;
    int& operator()(unsigned i, unsigned j);
    friend std::ostream& operator<<(std::ostream& ostr,
        const Instance& instance);
    
    unsigned size() const;
    Matrix matrix() const;
    long int totalSum() const;
    long int bestScore();

private:
    std::string filePath_;
    unsigned size_;
    Matrix matrix_;
    long int totalSum_;
    long int bestScore_;
};

std::ostream& operator<<(std::ostream& ostr, const Matrix& matrix);
bool operator==(const Matrix& a, const Matrix& b);

#endif // INSTANCE_HPP
