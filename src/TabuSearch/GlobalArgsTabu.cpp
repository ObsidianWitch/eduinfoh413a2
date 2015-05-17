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
    checkMin();
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

void GlobalArgsTabu::checkMin() const {
    bool err = (
        ttIterationsWoModification == 0 ||
        maxOccurencesFrequentlyEncountered == 0 ||
        maxCandidateTriggerEscape == 0 ||
        randomStepsEscape < 2
    );
    
    if (err) {
        std::cout << "Invalid argument (check range)" << std::endl;
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
              << " -m <ttIterationsWoModification (unsigned >= 1)>" << std::endl
              << "\t-o <maxOccurencesFrequentlyEncountered (unsigned >= 1)>" << std::endl
              << "\t-t <maxCandidateTriggerEscape (unsigned >= 1)>" << std::endl
              << "\t-r <randomStepsEscape (unsigned >= 2)>" << std::endl
              << "\t-f <instance_file>" << std::endl;
}
