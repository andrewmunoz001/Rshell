#include <string>
#include "Parse.h"

unsigned countQuotes(string);

Parse::Parse(const string& strUnparsed){
	commandTree = 0; // set pointer to 0 before anything is done    
	isvalid = false;
	bool vCheck = false;

	unsigned countOpen = 0;
	unsigned countClosed = 0;
	unsigned semiCount = 0;
	int pCheck = 0;

	//deletes # and anything past it
	/*string stringToParse = strUnparsed;
	for (unsigned i = 0; i < strUnparsed.size(); ++i) {
		if (strUnparsed.at(i) == '#') {
			stringToParse = strUnparsed.substr(0, i);
			break;
		}
	}*/

	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(" ");          // only seperate by spaces
	tokenizer tokens(strUnparsed, sep);          // seperate unparsed string into tokens

	for (tokenizer::iterator it = tokens.begin(); it != tokens.end(); it++){
		string temp = *it;
		if (countQuotes(temp) % 2 == 1) {
			//quotation extends past current token.
			string standby = temp; //fills with contents of quotations"
			it++;
			if (it != tokens.end()) {
				temp = *it;
			}
			while (countQuotes(temp) % 2 == 0) {
				standby.append(" " + temp);
				it++;
				if (it == tokens.end())
					break;
				temp = *it;
			}
			if (it != tokens.end()) {//only true if temp contains ending quote
				standby.append(" " + temp);
				temp = "";
			}
			if (standby != "")
				vLineInput.push_back(standby);
		}
		else if (countQuotes(temp) % 2 == 0 && countQuotes(temp) > 0) {
			vLineInput.push_back(temp);
			temp = "";
		}
	//Parse Comments(#)
		bool doBreak = false;
		for (unsigned i = 0; i < temp.size(); i++) {
			if (temp.at(i) == '#') {
				if (i > 0) {
					vLineInput.push_back(temp.substr(0, i-1));
				}
				while (it != tokens.end()) {
					++it;
				}
				doBreak = true;
			}
		}
		if (doBreak) {
			break;
		}
		
		// seperates semicolon from string
		if (temp == "")
			continue;
		if (temp.at(temp.size() - 1) == ';' && temp.size() > 1){      			
			//vLineInput.push_back(temp.substr(0, temp.size() - 1));   // push ;
			//
			//temp = temp.substr(temp.size() - 1, temp.size());        // redo string 
			temp = temp.substr(0, temp.size() - 1);
			semiCount++;
		}

		if (temp == "") 
			continue;
		// seperates '(' or ')' from the string
		while (temp.at(0) == '(') {
			countOpen++;
			if (temp.size() == 1) break;
			vLineInput.push_back("(");
			temp = temp.substr(1, temp.size()-1);
		}
		if (temp.size() == 0) continue;
		if (temp.at(temp.size()-1) == ')') {
			for (int i = (temp.size()-1); i >= 0; --i) {
				if (temp.at(i) != ')') {
					break;
				}
				else {
					++countClosed;
				}
			}
			if (temp.size() > countClosed) {
				vLineInput.push_back(temp.substr(0, temp.size()-countClosed));
			}
			//
			while (countClosed > 0) {
				vLineInput.push_back(")");
				countClosed--;
			}
			temp = "";
		}


		if (temp.size() != 0)
			vLineInput.push_back(temp);   // seperates each token into vector of strings
		if (semiCount != 0){
			vLineInput.push_back(";");
			semiCount = 0;
		}
	}
		// Test tokenizing 
	for (unsigned i = 0; i < vLineInput.size(); i++){
		if (vLineInput.at(i) == "(") 
			pCheck++;
		if (vLineInput.at(i) == ")")
			pCheck--;
		if (pCheck < 0){
			vCheck = true;
			break;
		}
	}
	if (pCheck == 0){
		isvalid = true;
	}
	if (isvalid == vCheck)
		isvalid = false;
	if (!vLineInput.empty()){
		vIterator = vLineInput.end(); 
		commandTree = turnToBase(vLineInput, vIterator);
	}
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
			if (rBase == 0 && !commandVec.empty()){
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
			if (rBase == 0 && !commandVec.empty()){
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
            if (rBase == 0 && !commandVec.empty()){
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
unsigned countQuotes(string check){
	unsigned ret = 0;
	for (unsigned i=0; i<check.size(); ++i){
		if (check.at(i) == '\"') {
			++ret;
		}
	}
	return ret;
}





