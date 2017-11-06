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
    public:
        // Connector will be initilized to empty string, unless a connector is passed through
        cmdLeaf(const vector<string>& iVector){
            cmdStr = iVector;
        };
        bool executeCommand();      // executes one command

        void showCommand();     // shows whats in the command object, used for testing
};

// Base Composite Class
class cmdComposite : public cmdBase{
    protected:
        cmdBase *left, *right;
    public:
        cmdComposite() : cmdBase(){};
        cmdComposite ( cmdBase* l, cmdBase* r): left(l), right(r){};

        virtual bool executeCommand() = 0;
};

// Composite Classes
class orConnector : public cmdComposite{
        public:
            orConnector(){};
            orConnector(cmdBase *l, cmdBase *r) : cmdComposite(l, r){};
            bool executeCommand(){
                if (this->left->executeCommand()){
                    return true;
                }
                else 
                    return this->right->executeCommand();
                
            };
};

#endif
