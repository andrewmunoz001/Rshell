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

void execute(vector<string> &vStr);

int main(int argc, char* argv[]){
    while(1){
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        boost::char_separator<char> sep(" ");          // only seperate by spaces

        string strInput;     // input from getline
        vector<string> vStr;

        printf("rshell beta $ ");
        getline(cin, strInput);           // get user input, put in str
        tokenizer tokens(strInput, sep);  // seperate strInput into tokens

        for(tokenizer::iterator it = tokens.begin();
                it != tokens.end();
                it++){
            string temp = *it;
            if (temp.at(temp.size() - 1) == ';'){       // seperates semicolon from string
                vStr.push_back(temp.substr(0,temp.size() - 1));  
                vStr.push_back(temp.substr(temp.size()-1, temp.size()));
            }
            else
                vStr.push_back(temp); // seperates each token into a vector of strings
        }
        
        if (vStr.size() == 0)      // if nothing was entered
            continue;              // do a new loop
        if (vStr.at(0) == "exit")
            return 0;             // exit function... please change
       
        cout << "Tokens in array:" << endl;
        for (unsigned i = 0; i < vStr.size(); i++){
            cout << "Token " << i << ": " << vStr.at(i) << endl;
        }
        execute(vStr);


    }
    return 0;
}


void execute(vector<string> &vStr){
    char* args[2];
    string temp = "ls";
    args[0] = (char*)vStr.at(0).c_str();
    args[1] = NULL;

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
}
