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
    
    // iterator points to beginning
    vIterator = vLineInput.begin(); 
    last = vLineInput.end();
    // Now start creating the tree 
    turnToBase(vLineInput, vIterator, last);
}

cmdBase* Parse::turnToBase(const vector<string>& sV,
    vector<string>::iterator& vIterator, vector<string>::iterator& last){

    cmdBase* rBase = 0; 
	vector<string> commandVec;

	while (vIterator != sV.end()) {
        if (*vIterator == "||") {
            vIterator++; // point to next string;
            turnToBase(vLineInput, vIterator, last);
            break;                
        }
        else if (*vIterator == "&&") {
            vIterator++; // point to next string;
            turnToBase(vLineInput, vIterator, last);
            break; 
        }
        else if (*vIterator == ";") {
            vIterator++; // point to next string;
            turnToBase(vLineInput, vIterator, last);
            break;
        }
        //recursive case
        /*else if (*vIterator == "(") {
            //find closing parenthesis (use count in case of
            //extra opening parentheses) and call turnToBase
            //on subVector within parentheses.
        }*/
        else {
            commandVec.push_back(*vIterator);
            vIterator++;
        }
	}
    // If loop ended, commandVec is still full, make it into cmdLeaf
    // rBase = new cmdLeaf(commandVec);
    cout << endl;
    for (unsigned i = 0; i < commandVec.size(); i++){
        cout << commandVec.at(i) << " ";
    }	
	return rBase;
}

void Parse::buildTree(){
}





