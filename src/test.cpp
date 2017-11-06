#include <iostream>
#include <unistd.h>      // fork() and execvp()
#include <sys/types.h>   // waitpid()
#include <sys/wait.h>    // waitpid()
#include <vector>
#include <boost/tokenizer.hpp>
#include <stdio.h>

#include <queue>

#include "Parse.h"
#include "cmdComponent.h"
#include "cmdComposite.h"

using namespace boost;
using namespace std;


int main(int argc, char* argv[]){

        while(1){
            string strInput;     // input from getline

            printf("rshell beta $ ");
            getline(cin, strInput);           // get user input, put in str

            string c1str1 = "ls";
            string c2str1 = "lss";
            string c3str1 = "ps";
            vector<string> c1;
            vector<string> c2;
            vector<string> c3;
            c1.push_back(c1str1);
            c2.push_back(c2str1);
            c3.push_back(c3str1);
            
            cmdBase* command1 = new cmdLeaf(c1);
            cmdBase* command2 = new cmdLeaf(c2);
            cmdBase* command3 = new cmdLeaf(c3);
            cmdBase* orCmd = new orConnector(command1,command2);
            cmdBase* compCmd = new semiConnector (orCmd, command3); 

            break;

        }
    
    return 0;
}


