#ifndef CMDCOMPOSITE_H 
#define CMDCOMPOSITE_H

#include "cmdComponent.h"

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> // fork() and execvp()
#include <sys/types.h>      // waitpid()
#include <sys/wait.h>       // waitpid()
#include <stdio.h>          // perror
#include <cstdlib>

using namespace std;

class cmdLeaf : public cmdBase{
    private:
        vector<string> cmdStr;
        string connectorType;
    public:
        // Connector will be initilized to empty string, unless a connector is passed through
        cmdLeaf(const vector<string>& iVector, const string& con){
            cmdStr = iVector;
            connectorType = con;
        };
        bool executeCommand();      // executes one command

        void showCommand();     // shows whats in the command object, used for testing
};

class cmdComposite : public cmdBase{
    protected:
        cmdBase* child;
    public:
        cmdComposite() : cmdBase(){};
        cmdComposite ( cmdBase* c): child(c){};

        bool executeChild() { return child->executeCommand(); };
        bool executeCommand();
};


#endif
