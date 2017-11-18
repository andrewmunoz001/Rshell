#ifndef PARSE_H
#define PARSE_H

#include <sstream>
#include <string>
#include <queue>
#include "cmdComponent.h"
#include "cmdComposite.h"
#include <boost/tokenizer.hpp>
#include <iostream>
#include <algorithm> // reverse()

using namespace boost;
using namespace std;

class Parse {
    private:
        vector<string> vLineInput;
        vector<string>::iterator vIterator;
        cmdBase* commandTree;

        bool isvalid;       // if input isnt invalid, this will return true
    public:
        // takes input, which is unparsed, and parses it into tokens 
        Parse(const string& strUnparsed);
        ~Parse(){
            if (commandTree != 0){
                delete commandTree;
                commandTree = 0;
            }
        }

        cmdBase* getTree(){ return commandTree; };
        bool getValidity(){ 
            if (commandTree == 0){
                //isvalid = false;
            }
            return isvalid; 
        };
    private:
        //turns input vector of strings into a single cmdBase*; calls
	    //itself if it hits parentheses
	    cmdBase* turnToBase(const vector<string>&, vector<string>::iterator&);
};



#endif
