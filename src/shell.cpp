#include <iostream>
#include <stdio.h>
#include "Parse.h"
#include "cmdComposite.h"

using namespace std;


int main(int argc, char* argv[]){

        while(1){
            string strInput;     // input from getline

            printf("rshell beta $ ");
            getline(cin, strInput);           // get user input, put in str
            Parse parsedLine(strInput);       // Parse the input
            parsedLine.getTree()->executeCommand(); // execute the command tree
        }
    
    return 0;
}


