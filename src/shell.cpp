#include <iostream>
#include <unistd.h>      // fork() and execvp()
#include <sys/types.h>   // waitpid()
#include <sys/wait.h>    // waitpid()
#include <vector>
#include <boost/tokenizer.hpp>
#include <stdio.h>
#include "Parse.h"
#include "command.h"

using namespace boost;
using namespace std;

void execute(Command& );

int main(int argc, char* argv[]){

        while(1){
            string strInput;     // input from getline

            printf("rshell beta $ ");
            getline(cin, strInput);           // get user input, put in str


        
            Parse parsedLine(strInput);
            parsedLine.print();

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
