#include <stdio.h>
#include "ArgsAnalyzer.h"

int main(int argc, const char** argv)
{
    ArgsAnalyzer analyzer;
    analyzer.setHelpHeaderString(
        "file binary expression print\n"
        "2021 (C)Misakichi\n"
        "Usage:\n"
        "\tfbep <option> inputs...\n"
        "Options:\n"
    );
    analyzer.addOption("help", "print this help.");
    analyzer.addOption("offset", "compare start offset(default:0)");
    analyzer.addOption("range", "compare range bytes(default:0xffffffffffffffff");
    analyzer.acceptValue(true);
    analyzer.printHelp();
    
    return 0;
}