#include <iostream>
#include <unistd.h>      // fork() and execvp()
#include <sys/types.h>   // waitpid()
#include <sys/wait.h>    // waitpid()
#include <vector>
#include <boost/tokenizer.hpp>
#include <stdio.h>
#include "Parse.h"
#include "command.h"
#include <queue>

using namespace boost;
using namespace std;

void execute(Command& );

int main(int argc, char* argv[]){

        while(1){
            string strInput;     // input from getline

            printf("rshell beta $ ");
            getline(cin, strInput);           // get user input, put in str


        
            string c1str1 = "lss";
            string c1connector = "||";
            string c2str1 = "ps";
            string c2connector = ";";
            string c3str1 = "exit";
            string c3connector = ";";
            vector<string> c1;
            vector<string> c2;
            vector<string> c3;
            c1.push_back(c1str1);
            c2.push_back(c2str1);
            c3.push_back(c3str1);
            Command cmd1(c1, c1connector);
            Command cmd2(c2, c2connector);
            Command cmd3(c3, c3connector);
            queue<Command> cmdqueue;
            cmdqueue.push(cmd1);
            cmdqueue.push(cmd2);
            cmdqueue.push(cmd3);

            while (!cmdqueue.empty()){   // if theres still commands to be executed
                if (cmdqueue.size() == 1){ // only one command
                    cmdqueue.front().executeCommand();
                    cmdqueue.pop();  // pop it, now its empty
                }
                else{
                    if (cmdqueue.front().executeNext())
                        cmdqueue.pop();
                    else{
                       cmdqueue.pop();
                       cmdqueue.pop(); 
                    }
                }
                
            }

            // THIS IS ONLY FOR TESTING
            //string testConnector = "";
            //Command testCommand(vStr,testConnector);
            //execute(testCommand);
        }
    
    return 0;
}


void execute(Command& inCmd){
    vector<string> execVector = inCmd.getCmdStr();
    unsigned elements = execVector.size();

    // Exit function
    if (execVector.at(0) == "exit"){
        if (execVector.size() != 1){
            printf("rshell: Error, too many arguments for exit!\n");
            return;
        }
        else
            exit(0);       // terminate normally    
    }
    
    char** args = new char*[elements + 1];       // needs 1 extra for the NULL char*

    for (unsigned i = 0; i < elements; i++){     // fill up char array with the arguments
        args[i] = (char*)(execVector.at(i).c_str());
    }
    args[elements] = NULL;         // make sure last element is set to null


    pid_t pid = fork();                    // fork value set to pid, of type pid_t

    if (pid < 0){   // if pid < 0, error in forking
        perror("ForkFailure");
    }
    if (pid == 0){  // if child process
        if (execvp(args[0], args) == -1){     // execvp(char* cmd, char* arg[])
        perror ("exec");
        }
        exit(1);
    }
    if (pid > 0){    // parent process
        wait(NULL);
    }
    delete [] args;       // make sure to deallocate the memory
}
