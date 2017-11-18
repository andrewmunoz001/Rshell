#include <iostream>
#include <stdio.h>
#include "Parse.h"
#include "cmdComposite.h"

using namespace std;


int main(int argc, char* argv[]){

        while(1){
            string strInput;     // input from getline

            printf("rshell $ ");
            getline(cin, strInput);           // get user input, put in str
            Parse parsedLine(strInput);       // Parse the input
            
            if (parsedLine.getValidity()){
                if (parsedLine.getTree() != 0)
                    parsedLine.getTree()->executeCommand(); 
                // execute command tree
            }
            else{
                printf("rshell: Invalid input\n");
            }
        }
    
    return 0;
}


