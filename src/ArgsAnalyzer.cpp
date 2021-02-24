#include "ArgsAnalyzer.h"
#include <string.h>

 

void ArgsAnalyzer::addOption(const char* name, const char* comment)
{
    paramDefinition_.push_back({name, comment, strlen(name), true});
}

void ArgsAnalyzer::addParam(const char* name, const char* comment)
{
    paramDefinition_.push_back({name, comment, strlen(name), false});
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
        printf("  -%s:%s\n", param.name.c_str(), param.comment.c_str());
    }
    puts(helpFooterStr_.c_str());
}