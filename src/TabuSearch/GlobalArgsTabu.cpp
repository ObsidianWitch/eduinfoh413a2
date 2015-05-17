#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "GlobalArgsTabu.hpp"

GlobalArgsTabu::GlobalArgsTabu(std::string programName) :
    programName(programName)
{}

void GlobalArgsTabu::retrieve(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "m:o:t:r:f:")) != -1) {
        switch(opt) {
            case 'm':
                ttIterationsWoModification = std::stoul(optarg);
                break;
            
            case 'o':
                maxOccurencesFrequentlyEncountered = std::stoul(optarg);
                break;
            
            case 't':
                maxCandidateTriggerEscape = std::stoul(optarg);
                break;
            
            case 'r':
                randomStepsEscape = std::stoul(optarg);
                break;
            
            case 'f':
                filePath = optarg;
                break;
            
            default:
                break;
        }
    }

    checkArgs();
}

void GlobalArgsTabu::checkArgs() const {
    checkEmpty();
    checkFilePath();
}

void GlobalArgsTabu::checkEmpty() const {
    bool empty = filePath.empty();
    
    if (empty) {
        std::cout << "Missing argument" << std::endl;
        printHelp();
        exit(EXIT_FAILURE);
    }
}

void GlobalArgsTabu::checkFilePath() const {
    std::ifstream ifs(filePath.c_str());
    
    if (!ifs.good()) {
        std::cout << "<instance_file> must exists and must be readable" << std::endl;
        exit(EXIT_FAILURE);
    }
}


void GlobalArgsTabu::printHelp() const {
    std::cout << "Usage:" << programName
              << " -m <ttItereationsWoModification (unsigned)>" << std::endl
              << "\t-o <maxOccurencesFrequentlyEncountered (unsigned)>" << std::endl
              << "\t-t <maxCandidateTriggerEscape (unsigned)>" << std::endl
              << "\t-r <randomStepsEscape (unsigned)>" << std::endl
              << "\t-f <instance_file>" << std::endl;
}
