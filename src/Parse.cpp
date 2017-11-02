#include "Parse.h"

Parse::Parse(const string& strUnparsed){
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(" "); // only seperate by spaces
    tokenizer tokens(strUnparsed, sep);      // seperate unparsed string into tokens

    for (tokenizer::iterator it = tokens.begin();
            it != tokens.end();
            it++){
        string temp = *it;
        if (temp.at(temp.size() - 1) == ';'){ // seperates semicolon from string
           vLineInput.push_back(temp.substr(0,temp.size() - 1));
           vLineInput.push_back(temp.substr(temp.size() - 1, temp.size())); 
        }
        else
            vLineInput.push_back(temp);   // seperate each token into vector of strings
    }
}

queue<Command> Parse::getCommandList(){
	queue<Command> parsedQueue;
	vector<string> subVector;
	string connector;

	for (unsigned i = 0; i < vLineInput.size(); ++i) {

		if (vLineInput.at(i) == "||" || vLineInput.at(i) == "&&" || vLineInput.at(i) == ";") {
			connector = vLineInput.at(i);
			parsedQueue.push(Command(subVector, connector));
			subVector.clear();
			connector = "";
		}

		else {
			subVector.push_back(vLineInput.at(i));
		}
	}
	
	if (!subVector.empty()){  // if subVector is still filled
		parsedQueue.push(Command(subVector, connector));   // add it to the queue
	}
	return parsedQueue;
}

void Parse::print(){
    if (vLineInput.size() != 0){
        for (unsigned i = 0; i < vLineInput.size(); i++){
            cout << vLineInput.at(i) << endl;
        }
    }
}
