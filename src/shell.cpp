#include <iostream>
#include <unistd.h>      // fork() and execvp()
#include <sys/types.h>   // waitpid()
#include <sys/wait.h>    // waitpid()
#include <vector>
#include <boost/tokenizer.hpp>
#include <stdio.h>

using namespace boost;
using namespace std;

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
            vStr.push_back(*it); // seperates each token into a vector of strings
            // this is pushback is temporary until a better way is found!!!!!
        }
        
        if (vStr.size() == 0)      // if nothing was entered
            continue;              // do a new loop
        if (vStr.at(0) == "exit")
            return 0;             // exit function... please change
       
        cout << "Tokens in array:" << endl;
        for (unsigned i = 0; i < vStr.size(); i++){
            cout << "Token " << i << ": " << vStr.at(i) << endl;
        }


    }






    return 0;
}
