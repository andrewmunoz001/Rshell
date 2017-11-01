#include "command.h"

Command::Command(){
    cmdStr;
    connectorType = "";
}

Command::Command(const vector<string>& iVector, const string& con){
    cmdStr = iVector;            // copies value of vector into cmdStr Vector
    connectorType = con;         // sets the connector type for the command
}
