#include <iostream>
#include <fstream>
#include <unistd.h>
#include "GlobalArgsII.hpp"

GlobalArgsII::GlobalArgsII(std::string programName) : programName(programName) {}

void GlobalArgsII::retrieve(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "i:p:n:f:")) != -1) {
        switch(opt) {
            case 'i':
                init = optarg;
                break;
            
            case 'p':
                pivoting = optarg;
                break;
            
            case 'n':
                neighbourhood = optarg;
                break;
            
            case 'f':
                filePath = optarg;
                break;
            
            default:
                break;
        }
    }
}

void GlobalArgsII::checkArgs() const {
    checkEmpty();
    checkInitialization();
    checkPivotingRule();
    checkNeighborhood();
    checkFilePath();
}

void GlobalArgsII::checkEmpty() const {
    bool empty = init.empty() || pivoting.empty() || neighbourhood.empty() ||
        filePath.empty();
    
    if (empty) {
        std::cout << "Missing argument" << std::endl;
        printHelp();
        exit(EXIT_FAILURE);
    }
}

void GlobalArgsII::checkInitialization() const {
    bool valid = (init == "cw") || (init == "random");
    
    if (!valid) {
        std::cout << "<initialization_rule> must be one of the following: cw,"
                  << " random" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GlobalArgsII::checkPivotingRule() const {
    bool valid = (pivoting == "first") || (pivoting == "best");
    
    if (!valid) {
        std::cout << "<pivoting_rule> must be one of the following: first, best"
                  << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GlobalArgsII::checkNeighborhood() const {
    bool valid = (neighbourhood == "transpose") ||
                 (neighbourhood == "exchange") ||
                 (neighbourhood == "insert");
    
    if (!valid) {
        std::cout << "<neighbourhood> must be one of the following:"
                  << " transpose, exhange, insert" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GlobalArgsII::checkFilePath() const {
    std::ifstream ifs(filePath.c_str());
    
    if (!ifs.good()) {
        std::cout << "<instance_file> must exists and must be readable" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GlobalArgsII::printHelp() const {
    std::cout << "Usage:" << programName
              << " -i <initialization_rule (cw|random)>" << std::endl
              << "\t-p <pivoting_rule (first|best)>" << std::endl
              << "\t-n <neighbourhood (transpose|exchange|insert)>" << std::endl
              << "\t-f <instance_file>" << std::endl;
}
