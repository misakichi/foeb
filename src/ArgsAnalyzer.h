#ifndef _ARGS_ANALYZER_H
#define _ARGS_ANALYZER_H

#include <vector>
#include <string>
#include <map>

class ArgsAnalyzer 
{
public:

	//these functions are called to setup arguments.
	//it after, call 'analyze' functions.
    void acceptValue(bool enable) { acceptValue_ = enable; }
    void setHelpHeaderString(const char* str) { helpHeaderStr_ = str; }
    void setHelpFooterString(const char* str) { helpFooterStr_ = str; }
    void addOption(const char* name, const char* comment, const char* defaultValue);
    void addParam(const char* name, const char* comment, const char* defaultValue);
    void printHelp();

    bool analyze(int argc, const char** args);

	//after the 'analyze' functions are called, call these functions.
	const std::vector<std::string>& values() const { return values_; }
	bool hasParam(const char* name) const;
	bool isOnOption(const char* name) const;
	const char* getParameter(const char* name) const;

private:
    struct ParamDefinition {
        std::string name;
        std::string comment;
		std::string defaultValue;
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