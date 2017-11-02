#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <unistd.h> // fork() and execvp()
#include <sys/types.h>      // waitpid()
#include <sys/wait.h>       // waitpid()
#include <stdio.h>          // perror
#include <cstdlib>

using namespace std;

class Command {
    private:
        vector<string> cmdStr;
        string connectorType;
    public:
        // Connector will be initilized to empty string, unless a connector is passed through
        Command(const vector<string>& iVector, const string& con);
        bool executeCommand();      // executes one command
        bool executeNext();         // uses connectors 
        vector<string> getCmdStr();     // returns the vector of commands
        void showCommand();     // shows whats in the command object, used for testing
};


#endif
