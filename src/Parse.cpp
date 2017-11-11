#include "Parse.h"

Parse::Parse(const string& strUnparsed){
    commandTree = 0; // set pointer to 0 before anything is done    
    isvalid = false;

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
            vLineInput.push_back(temp.substr(0, temp.size() - 1));   // push ;
            temp = temp.substr(temp.size() - 1, temp.size());        // redo string 
         }
        
        // seperates '(' or ')' from the string
        //int pCount = 0; // Counts Parenthesis, if != 0 error
        //int bCount = 0; // Counts Brackets, if != error
        if (temp.size() != 0)
            vLineInput.push_back(temp);   // seperates each token into vector of strings
    }
    
    // Test tokenizing 
    
    /*
    for (unsigned i = 0; i < vLineInput.size(); i++){
       cout << vLineInput.at(i) << endl;
    }*/
    
    // iterator points to beginning
    isvalid = true;
    vIterator = vLineInput.end(); 
    commandTree = turnToBase(vLineInput, vIterator);
}

cmdBase* Parse::turnToBase(const vector<string>& sV,vector<string>::iterator& vIterator){

    cmdBase* rBase = 0; 
	vector<string> commandVec;

	while (vIterator != sV.begin()) {
            vIterator--;
        if (*vIterator == "("){
            break;        
            }
        if (*vIterator == "]")
            vIterator--;
        if (*vIterator == "||") {
            if (rBase == 0){
                reverse(commandVec.begin(), commandVec.end());
                cmdBase* right = new cmdLeaf(commandVec); // create leaf
                rBase = new orConnector(turnToBase(vLineInput,vIterator), right); 
            }
            else{
                cmdBase* temp = rBase;
                rBase = new orConnector(turnToBase(vLineInput, vIterator), temp);
            }
            return rBase;
        }
        else if (*vIterator == "&&") {
            if (rBase == 0){
                reverse(commandVec.begin(), commandVec.end());
                cmdBase* right = new cmdLeaf(commandVec); // create leaf
                rBase = new andConnector(turnToBase(vLineInput,vIterator), right); 
            }
            else{
                cmdBase* temp = rBase;
                rBase = new andConnector(turnToBase(vLineInput, vIterator), temp);
            }
            return rBase;
        }
        else if (*vIterator == ";") {
            if (rBase == 0){
                reverse(commandVec.begin(), commandVec.end());
                cmdBase* right = new cmdLeaf(commandVec); // create leaf
                rBase = new semiConnector(turnToBase(vLineInput,vIterator), right); 
            }
            else{
                cmdBase* temp = rBase;
                rBase = new semiConnector(turnToBase(vLineInput, vIterator), temp);
            }
            return rBase;
        }
        //recursive case
        else if (*vIterator == ")") {
            //find opening parenthesis 
            rBase = turnToBase(vLineInput, vIterator);
            }

        else {
            // If it isn't a connector, it must be a command arg. Build the vector
            commandVec.push_back(*vIterator);
        }
	}

    // If loop ended, commandVec is still full, make it into cmdLeaf
    // since the vector was built backwards, we have to flip before creating an object
    if (!commandVec.empty()){
        reverse(commandVec.begin(), commandVec.end());
        rBase = new cmdLeaf(commandVec);
    }
    
    return rBase;
}






