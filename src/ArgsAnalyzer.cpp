#include "ArgsAnalyzer.h"
#include <string.h>
#include <algorithm>
 

void ArgsAnalyzer::addOption(const char* name, const char* comment, const char* defaultValue)
{
    paramDefinition_.push_back({name, comment, defaultValue, strlen(name), true});
}

void ArgsAnalyzer::addParam(const char* name, const char* comment, const char* defaultValue)
{
    paramDefinition_.push_back({name, comment, defaultValue, strlen(name), false});
}

bool ArgsAnalyzer::analyze(int argc, const char** args)
{
    for(int i=1; i<argc; i++)
    {
        bool found = false;
        if(args[i][0]=='-') 
        {
            auto arg = args[i]+1;
            auto argLen = strlen(arg);
            for(auto& param : paramDefinition_) 
            {
                if(param.nameLen<=argLen && strncmp(param.name.c_str(), arg, param.nameLen)==0)
                {
                    found = true;
                    analyzedParam_[param.name] = param.isOption ? "1" : arg+param.nameLen;
                    break;
                }
            }
        }
        if(!found) 
        {
            if(acceptValue_ && args[i][0]!='-')
            {
                values_.push_back(args[i]);
            }
            else
            {
                printf("invalid argment %s\n", args[i]);
                return false;
            }
        }
    }

    return true;
}

void ArgsAnalyzer::printHelp()
{
    puts(helpHeaderStr_.c_str());
    for(auto& param : paramDefinition_) 
    {
        printf("  -%-10s%s\n", param.name.c_str(), param.comment.c_str());
    }
    puts(helpFooterStr_.c_str());
}

bool ArgsAnalyzer::hasParam(const char* name) const
{
	return analyzedParam_.find(name) != analyzedParam_.end();
}

bool ArgsAnalyzer::isOnOption(const char* name) const
{
	auto itParam = std::find_if(paramDefinition_.begin(), paramDefinition_.end(), [name](const ParamDefinition& param) { return param.name == name; });
	if (itParam == paramDefinition_.end())
		return false;
	if (!itParam->isOption)
		return false;

	auto itValue = analyzedParam_.find(name);
	auto& value = itValue == analyzedParam_.end() ? itParam->defaultValue :  itValue->second;
	return atoi(value.c_str()) != 0;
}

const char* ArgsAnalyzer::getParameter(const char* name) const
{
	auto itParam = std::find_if(paramDefinition_.begin(), paramDefinition_.end(), [name](const ParamDefinition& param) { return param.name == name; });
	if (itParam == paramDefinition_.end())
		return nullptr;
	if (itParam->isOption)
		return nullptr;

	auto itValue = analyzedParam_.find(name);
	auto& value = itValue == analyzedParam_.end() ? itParam->defaultValue:  itValue->second;
	return value.c_str();
}
