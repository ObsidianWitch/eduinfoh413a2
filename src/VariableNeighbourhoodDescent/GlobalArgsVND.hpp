#ifndef GLOBAL_ARGS_VND_HPP
#define GLOBAL_ARGS_VND_HPP

struct GlobalArgsVND {
    std::string programName;
    std::string neighbourhood;
    std::string filePath;
    
    GlobalArgsVND(std::string programName);
    
    void retrieve(int argc, char *argv[]);
    
    void checkArgs() const;
    void checkEmpty() const;
    void checkNeighborhood() const;
    void checkFilePath() const;
    
    void printHelp() const;
};

#endif // GLOBAL_ARGS_VND_HPP
