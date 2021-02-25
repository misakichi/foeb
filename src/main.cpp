#include <stdio.h>
#include "src/ArgsAnalyzer.h"
#include "src/common.h"
#include <algorithm>

int main(int argc, const char** argv)
{
    ArgsAnalyzer analyzer;
    analyzer.setHelpHeaderString(
        "Find and Output Equal Binaries.\n"
        "2021 (C)Misakichi\n"
        "Usage:\n"
        "  foeb [option]... search_data inputs...\n"
		"  search_data is hex format. (e.g ff0077 is 3 byte data)\n"
		"ex. foeb -offset0x20 -range0x100 ff777777 image*.tga"
		"   search the 3 byte<0xff 0x00 0x77> on 0x20-0x120 range in image*.tga.\n"
		"\n"
        "Options:"
    );
    analyzer.addOption("help", "print this help.", "0");
    analyzer.addParam("offset", "compare start offset(default:0)", "0");
    analyzer.addParam("range", "compare range bytes(default:0xffffffffffffffff)", "0xffffffffffffffff");
    analyzer.acceptValue(true);
    auto analyzeSuccess = analyzer.analyze(argc,argv);
    auto& values = analyzer.values();

    if(!analyzeSuccess && values.size()<2)
    {
        return ERRCODE(1);
    }
    auto dataStr = values[0];
	for (auto& c : dataStr)
		c = tolower(c); 
	if (std::find_if(dataStr.begin(), dataStr.end(), [](char c) { return !(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f'); }) != dataStr.end())
	{
		printf("found invalid char(s) from search_data.\n");
		return ERRCODE(2);
	}

	printf("help=%d\n", analyzer.isOnOption("help") != false);
	printf("offset=%s\n", analyzer.getParameter("offset"));
	printf("range=%s\n", analyzer.getParameter("range"));

	printf("values:\n");
	for (auto& value : values)
		printf(" %s\n", value.c_str());
    
    return 0;
}