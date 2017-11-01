#ifndef PARSE_H
#define PARSE_H
#include <sstream>
#include <string>
#include <vector>
#include "command.h"

using namespace std;

class Parse {
    private:
        vector<Command> commandList;
    public:
        Parse();
        Parse(vector<string> &vStr);
};



#endif
