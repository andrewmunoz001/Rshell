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
#include <fcntl.h>      // macros 

using namespace std;

class cmdLeaf : public cmdBase{
    private:
        vector<string> cmdStr;
        bool test();
    public:
        cmdLeaf(const vector<string>& iVector){
            cmdStr = iVector;
        };
        bool executeCommand(int fdin = 0, int fdout = 1);      // executes one command
        bool ispipe(){ return false; }; // for piping 
        string getfile(){ return cmdStr.at(0); };
        
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

        virtual bool executeCommand(int fdin = 0, int fdout = 1) = 0;
        bool ispipe(){ 
        return false; };
        string getfile(){return "";};
};

/*  Base class for different types of pipes / redirection   */
class redirect : public cmdBase{
    protected:
        cmdBase *left, *right;
    public:
        redirect() : cmdBase(){};
        redirect( cmdBase* l, cmdBase* r ) : left(l), right(r){};
        ~redirect(){
            if (left != 0){
                delete left;
                left = 0;
            }
            if (right != 0){
                delete right;
                right = 0;
            }
        }
        virtual bool executeCommand(int, int) = 0;
        virtual bool ispipe(){ return true; };
        string getfile(){return "";};
};

class pipeConnector : public redirect{
    public:
        pipeConnector();
        pipeConnector(cmdBase *l, cmdBase *r);
        bool executeCommand(int, int);
};

/*      "<"     */
class inputConnector : public redirect{
    private:
        char* file[2];
    public:
        inputConnector();
        inputConnector(cmdBase *l, cmdBase *r);
        bool executeCommand(int, int);
};

/*      ">"     */
class outputConnector : public redirect{
    private:
        const char* file[2];
    public:
        outputConnector();
        outputConnector(cmdBase *l, cmdBase *r);
        bool executeCommand(int, int);
};

/*      ">>"     */
class appendConnector : public redirect{
    private:
        char* file[2];
    public:
        appendConnector();
        appendConnector(cmdBase *l, cmdBase *r);
        bool executeCommand(int, int);
};
/*  **** End Pipe Classes **** */

// Composite Classes
class orConnector : public cmdComposite{
        public:
            orConnector(){};
            orConnector(cmdBase *l, cmdBase *r) : cmdComposite(l, r){};
            bool executeCommand(int fdin = 0, int fdout = 1){
                if (this->left != 0 && this->left->executeCommand(fdin, fdout)){
                    return true;
                }
                else if (this->right != 0 && this->right->executeCommand(fdin, fdout)){
                    return true;
                } 
                else
                    return false;
            };
};

class andConnector : public cmdComposite{
  public:
	andConnector();
	andConnector(cmdBase* l, cmdBase* r): cmdComposite(l,r){};
	bool executeCommand(int fdin = 0, int fdout = 1) {
        if (this->left != 0 && this->left->executeCommand()) {
            if (this->right != 0 && this->right->executeCommand(fdin, fdout)) {
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
	bool executeCommand(int fdin = 0, int fdout = 1) {
        if (this->left != 0){
            this->left->executeCommand();
        }
        if (this->right != 0 && this->right->executeCommand(fdin, fdout)){
            return true;
        }
        else
            return false;
	};
};

#endif
