#include <iostream>
#include <fstream>
#include <unistd.h>
#include "GlobalArgsVND.hpp"

GlobalArgsVND::GlobalArgsVND(std::string programName) : programName(programName) {}

void GlobalArgsVND::retrieve(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "n:f:")) != -1) {
        switch(opt) {
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

void GlobalArgsVND::checkArgs() const {
    checkEmpty();
    checkNeighborhood();
    checkFilePath();
}

void GlobalArgsVND::checkEmpty() const {
    bool empty = neighbourhood.empty() || filePath.empty();
    
    if (empty) {
        std::cout << "Missing argument" << std::endl;
        printHelp();
        exit(EXIT_FAILURE);
    }
}

void GlobalArgsVND::checkNeighborhood() const {
    bool valid = (neighbourhood == "tei") ||
                 (neighbourhood == "tie");
    
    if (!valid) {
        std::cout << "<neighbourhood> must be one of the following: "
                  << "tei (transpose-exchange-insert), "
                  << "tie (transpose-insert-exchange)" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GlobalArgsVND::checkFilePath() const {
    std::ifstream ifs(filePath.c_str());
    
    if (!ifs.good()) {
        std::cout << "<instance_file> must exists and must be readable" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GlobalArgsVND::printHelp() const {
    std::cout << "Usage:" << programName
              << " -n <neighbourhood (tei|tie)>" << std::endl
              << "\t-f <instance_file>" << std::endl;
}
