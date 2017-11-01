#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

using namespace std;

class Command {
    private:
        vector<string> cmdStr;
        string connectorType;
    public:
        Command();   
        // Connector will be initilized to empty string, unless a connector is passed through
        Command(const vector<string>& iVector, const string& con);
};


#endif
