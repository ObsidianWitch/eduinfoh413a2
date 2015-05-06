#include <fstream>
#include <sstream>
#include "Instance.hpp"

Instance::Instance(std::string filePath) :
    filePath_(filePath), totalSum_(0), bestScore_(-1)
{
    parseToMatrix();
}

void Instance::parseToMatrix() {
    std::ifstream ifs(filePath_.c_str());
    std::stringstream ss;
    ss << ifs.rdbuf();
    
    // instance size
    ss >> size_;
    
    // Matrix
    matrix_ = Matrix(size_, MatrixRow(size_));
    for (unsigned i = 0 ; i < size_ ; i++) {
        for (unsigned j = 0 ; j < size_ ; j++) {
            ss >> matrix_[i][j];
            totalSum_ += matrix_[i][j];
        }
    }
}

long int Instance::evaluate(Permutation& p) const {
    long int score = 0;
    
    for (unsigned i = 0 ; i < size() ; i++) {
        for (unsigned j = i + 1 ; j < size() ; j++) {
            score += matrix_[p[i]][p[j]];
        }
    }
    
    p.setScore(score);
    
    return score;
}

long int Instance::evaluate(Permutation& p, const Neighbourhood& n) const {
    long int delta = n.delta(matrix_, p);
        
    long int score = p.score() + delta;
    
    return score;
}


void Instance::permuteRows(const Permutation& p) {
    Matrix copyMatrix(matrix_);
    
    for (unsigned i = 0 ; i < size() ; i++) {
        matrix_[i] = copyMatrix[p[i]];
    }
}

std::string Instance::toStringMatrixPermutation(const Permutation& p) const {
    return toStringMatrixPermutation(matrix_, p);
}

std::string Instance::toStringMatrixPermutation(const Matrix& matrix,
    const Permutation& p)
{
    std::ostringstream os;
    unsigned size = p.size();
    
    os << "[" << size << "," << size << "]" << "(";
    
    for (unsigned i = 0 ; i < size ; i++) {
        os << "(";
        
        for (unsigned j = 0 ; j < size ; j++) {
            os << matrix[p[i]][p[j]];
            
            if (j < size - 1) {
                os << ",";
            }
        }
        
        os << ")";
        
        if (i < size - 1) {
            os << ",";
        }
    }
    
    os << ")";
    
    return os.str();
}

int Instance::operator()(unsigned i, unsigned j) const {
    return matrix_[i][j];
}

int& Instance::operator()(unsigned i, unsigned j) {
    return matrix_[i][j];
}

unsigned Instance::size() const { return size_; }
Matrix Instance::matrix() const { return matrix_; }
long int Instance::totalSum() const { return totalSum_; }

long int Instance::bestScore() {
    if (bestScore_ != -1) {
        return bestScore_;
    }
    
    std::ifstream ifs("../best_known/best_known.txt");
    std::stringstream ss;
    ss << ifs.rdbuf();
    
    while (ifs.good()) {
        std::string fileName;
        long int bestScore;
        
        ss >> fileName >> bestScore;
        
        if (filePath_.find(fileName) != std::string::npos) {
            bestScore_ = bestScore;
            break;
        }
    }
    
    return bestScore_;
}

std::ostream& operator<<(std::ostream& ostr, const Instance& instance) {
    return operator<<(ostr, instance.matrix_);
}

std::ostream& operator<<(std::ostream& ostr, const Matrix& matrix) {
    Permutation p(matrix.size());
    std::string str = Instance::toStringMatrixPermutation(matrix, p);
    
    ostr << str;
    
    return ostr;
}

bool operator==(const Matrix& a, const Matrix& b) {
    if (a.size() != b.size()) {
        return false;
    }
    
    for (unsigned i = 0 ; i < a.size() ; i++) {
        for (unsigned j = 0 ; j < b.size() ; j++) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    
    return true;
}
