#ifndef PARSE_H
#define PARSE_H

#include <sstream>
#include <string>
#include <queue>
#include "cmdComponent.h"
#include "cmdComposite.h"
#include <boost/tokenizer.hpp>
#include <iostream>

using namespace boost;
using namespace std;

class Parse {
    private:
        vector<string> vLineInput;
        cmdBase* commandTree;
    public:
        // takes input, which is unparsed, and parses it into tokens 
        Parse(const string& strUnparsed);

        cmdBase* getTree(){ return commandTree; };
        //tests if tokenizer is funtioning
        void print();
    private:
        void buildTree();
};



#endif
