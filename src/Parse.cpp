#include "Parse.h"

Parse::Parse(){
}

Parse::Parse(vector<string> &vStr){
	queue<Command> parsedQueue;
	vector<string> subVector;
	string connector;
	for (unsigned i = 0; i < vStr.size(); ++i) {
		if (vStr.at(i) != "||" || vStr.at(i) != "&&" || vStr.at(i) != ";") {
			subVector.push_back(vStr.at(i));
		}
		else {
            connector = vStr.at(i);
			parsedQueue.push(Command(subVector, connector));
			subVector.clear();
			connector = "";
		}
	}
	commandList = parsedQueue;
}

void Parse::print(){
    commandList.front().showCommand();
}
