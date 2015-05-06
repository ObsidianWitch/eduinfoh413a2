#ifndef GLOBAL_ARGS_II_HPP
#define GLOBAL_ARGS_II_HPP

struct GlobalArgsII {
    std::string programName;
    std::string init;
    std::string pivoting;
    std::string neighbourhood;
    std::string filePath;
    
    GlobalArgsII(std::string programName);
    
    void retrieve(int argc, char *argv[]);
    
    void checkArgs() const;
    void checkEmpty() const;
    void checkInitialization() const;
    void checkPivotingRule() const;
    void checkNeighborhood() const;
    void checkFilePath() const;
    
    void printHelp() const;
};

#endif // GLOBAL_ARGS_II_HPP
