#ifndef _ARGS_ANALYZER_H
#define _ARGS_ANALYZER_H

#include <vector>
#include <string>
#include <map>

class ArgsAnalyzer 
{
public:

    void acceptValue(bool enable) { acceptValue_ = enable; }
    void setHelpHeaderString(const char* str) { helpHeaderStr_ = str; }
    void setHelpFooterString(const char* str) { helpFooterStr_ = str; }
    void addOption(const char* name, const char* comment);
    void addParam(const char* name, const char* comment);
    bool analyze(int argc, const char** args);
    void printHelp();


private:
    struct ParamDefinition {
        std::string name;
        std::string comment;
        size_t      nameLen;
        bool isOption;
    };
    bool                            acceptValue_ = false;
    std::vector<ParamDefinition>    paramDefinition_;
    std::string                     helpHeaderStr_;
    std::string                     helpFooterStr_;
    std::map<std::string, std::string>  analyzedParam_;
    std::vector<std::string>            values_;
};



#endif //!defined(_ARGS_ANALYZER_H)