#ifndef CMDCOMPOSITE_H 
#define CMDCOMPOSITE_H

#include "cmdComponent.h"

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> // fork() and execvp()
#include <sys/types.h>      // waitpid()
#include <sys/wait.h>       // waitpid()
#include <sys/stat.h>       // test command
#include <stdio.h>          // perror
#include <cstdlib>

using namespace std;

class cmdLeaf : public cmdBase{
    private:
        vector<string> cmdStr;
        bool test();
    public:
        cmdLeaf(const vector<string>& iVector){
            cmdStr = iVector;
        };
        bool executeCommand();      // executes one command
};

// Base Composite Class
class cmdComposite : public cmdBase{
    protected:
        cmdBase *left, *right;
    public:
        cmdComposite() : cmdBase(){};
        cmdComposite ( cmdBase* l, cmdBase* r): left(l), right(r){};
        ~cmdComposite(){
            if (left != 0){
                delete left;
                left = 0;
            }
            if (right != 0){
                delete right;
                right = 0;
            }
        }

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

class andConnector : public cmdComposite{
  public:
	andConnector();
	andConnector(cmdBase* l, cmdBase* r): cmdComposite(l,r){};
	bool executeCommand() {
		if (this->left->executeCommand()) {
			if (this->right->executeCommand()) {
				return true;
			}
		}
		return false;
	};
};

class semiConnector : public cmdComposite{
  public:
	semiConnector();
	semiConnector(cmdBase* l, cmdBase* r): cmdComposite(l,r){};
	bool executeCommand() {
		this->left->executeCommand();
		return this->right->executeCommand();
	};
};

#endif
