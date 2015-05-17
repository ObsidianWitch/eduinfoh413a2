#ifndef GLOBAL_ARGS_TABU_HPP
#define GLOBAL_ARGS_TABU_HPP

/**
 * This class retrieve command line arguments used by the tabu search.
 */
class GlobalArgsTabu {
public:
    std::string programName;
    std::string filePath;
    unsigned ttIterationsWoModification;
    unsigned maxOccurencesFrequentlyEncountered;
    unsigned maxCandidateTriggerEscape;
    unsigned randomStepsEscape;
    
    GlobalArgsTabu(std::string programName);

    void retrieve(int argc, char *argv[]);

    void printHelp() const;

private:
    void checkArgs() const;
    void checkEmpty() const;
    void checkMin() const;
    void checkFilePath() const;
};

#endif // GLOBAL_ARGS_TABU_HPP
