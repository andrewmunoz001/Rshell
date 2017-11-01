#ifndef PARSE_H
#define PARSE_H
#include <sstream>
#include <string>
#include <queue>
#include "command.h"

using namespace std;

class Parse {
    private:
        queue<Command> commandList;
    public:
        Parse();
        Parse(vector<string> &vStr);
        void print();
};



#endif
