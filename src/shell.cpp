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


int main(int argc, char* argv[]){

	while(1){
		string strInput;     // input from getline

		printf("rshell beta $ ");
		getline(cin, strInput);           // get user input, put in str



		Parse parsedLine(strInput);
		queue<Command> cmdqueue = parsedLine.getCommandList();
		while (!cmdqueue.empty()){
			if (cmdqueue.size() == 1){ // only one command
				cmdqueue.front().executeCommand();
				cmdqueue.pop();  // pop it, now its empty
			}
			else{
				if (cmdqueue.front().executeNext()) {
					cmdqueue.pop();
				}
				else {
					cmdqueue.pop();
					cmdqueue.pop();
				}
			}
		}
	}
	return 0;
}
