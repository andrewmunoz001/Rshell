#include "Parse.h"

Parse::Parse(const string& strUnparsed){
    
    //deletes # and anything past it
    string stringToParse = strUnparsed;
    for (unsigned i = 0; i < strUnparsed.size(); ++i) {
         if (strUnparsed.at(i) == '#') {
             stringToParse = strUnparsed.substr(0, i);
             break;
         }
     }
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(" ");          // only seperate by spaces
    tokenizer tokens(stringToParse, sep);          // seperate unparsed string into tokens

    for (tokenizer::iterator it = tokens.begin();
            it != tokens.end();
            it++){
        string temp = *it;

        if (temp.at(temp.size() - 1) == ';'){      // seperates semicolon from string
            vLineInput.push_back(temp.substr(0, temp.size() - 1));                
            vLineInput.push_back(temp.substr(temp.size() - 1, temp.size()));
         }

        else
            vLineInput.push_back(temp);   // seperates each token into vector of strings
    }
    
    // Now start creating the objects

    buildTree();
}

void Parse::buildTree(){
}





