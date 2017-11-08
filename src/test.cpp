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
            Parse parseobject(strInput);
            parseobject.getTree()->executeCommand();
            
        }
    
    return 0;
}


