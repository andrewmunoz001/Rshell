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
        vector<string>::iterator vIterator;
        cmdBase* commandTree;
    public:
        // takes input, which is unparsed, and parses it into tokens 
        Parse(const string& strUnparsed);

        cmdBase* getTree(){ return commandTree; };
        //tests if tokenizer is funtioning
        void print();
	    
    private:
        //turns input vector of strings into a single cmdBase*; calls
	    //itself if it hits parentheses
	    cmdBase* turnToBase(const vector<string>&, vector<string>::iterator&);

        // calls turnToBase function
	    void buildTree();
};



#endif
