#include "command.h"


#include <iostream>
using namespace std;

Command::Command(const vector<string>& iVector, const string& con = ""){
    cmdStr = iVector;            // copies value of vector into cmdStr Vector
    connectorType = con;         // sets the connector type for the command
}

vector<string> Command::getCmdStr(){
    vector<string> rStr = cmdStr;
    return rStr;
}

void Command::showCommand(){
    cout << endl << "arg list: ";
    for (unsigned i = 0; i < cmdStr.size(); i++){
        cout << cmdStr.at(i);
    }
    cout << endl << "connector: " << connectorType << endl;
}
