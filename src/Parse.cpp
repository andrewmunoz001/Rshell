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

cmdBase* turnToBase(vector<string> sv) {
	cmdBase* toReturn;
	vector<string> tempVec;
	string temp;
	for (int i = 0; i < sv.size(); ++i) {
		if (sv.at(i) == "||") {
			
		}
		else if (sv.at(i) == "&&") {
			
		}
		else if (sv.at(i) == ";") {
			
		}
		//recursive case
		else if (sv.at(i) == "(") {
			//find closing parenthesis (use count in case of
			//extra opening parentheses) and call turnToBase
			//on subVector within parentheses.
		}
		else {
			tempVec.push_back(sv.at(i));
		}
	}
	
	return toReturn;
}

void Parse::buildTree(){
}





