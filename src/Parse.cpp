#include "Parse.h"

Parse::Parse(){
}

Parse::Parse(vector<string> &vStr){
	queue<Command> parsedQueue;
	vector<string> subVector;
	string connector;
	for (unsigned i = 0; i < vStr.size(); ++i) {
		if (vStr.at(i) == "||" || vStr.at(i) == "&&") {
			connector = vStr.at(i);
			parsedQueue.push_back(Command(subVector, connector));
			subVector.clear();
			connector = "";
		}
		else if (vStr.at(i).at(vStr.at(i).size() - 1) == ';') {
			subVector.push_back(vStr.at(i).substr(0, vStr.at(i).size() - 1));
			connector = ';';
			parsedQueue.push_back(Command(subVector, connector));
			subVector.clear();
			connector = "";
		}
		else {
			subVector.push_back(vStr.at(i);
		}
	}
	
	commandList = parsedQueue;
}
