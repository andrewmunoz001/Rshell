#ifndef PARSE_H
#define PARSE_H
#include <sstream>
#include <string>
#include <queue>
#include "command.h"
#include <boost/tokenizer.hpp>
#include <iostream>

using namespace boost;
using namespace std;

class Parse {
    private:
        vector<string> vLineInput;

        queue<Command> commandList;
    public:
        // takes input, which is unparsed, and parses it 
        Parse(const string& strUnparsed);
        Parse(vector<string> &vStr);
        void print();
};



#endif
