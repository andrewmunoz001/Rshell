#include "command.h"


#include <iostream>
using namespace std;

Command::Command(const vector<string>& iVector, const string& con = ""){
    cmdStr = iVector;            // copies value of vector into cmdStr Vector
    connectorType = con;         // sets the connector type for the command
}

vector<string> Command::getCmdStr(){
    vector<string> rStr = cmdStr;
    return rStr;
}

bool Command::executeCommand(){
    unsigned elements = cmdStr.size();
    int returnStatus;

    // Exit function
    if (cmdStr.at(0) == "exit"){
        if (cmdStr.size() != 1){
            printf("rshell: Error, too many arguments for exit!\n");
            return false;
        }
        else
            exit(0);      // terminates the program
    }

    char** args = new char*[elements + 1];  // needs 1 extra for the NULL char*

    for (unsigned i = 0; i < elements; i++){ // fill up char array with the arguments
        args[i] = (char*)(cmdStr.at(i).c_str());
    }
    args[elements] = NULL; // make sure last element is set to null (For execvp to work)

    pid_t pid = fork(); // fork value set to pid, of type pid_t

    if (pid < 0){           // if pid < 0, error in forking
        perror("ForkFailure");
    }
    if (pid == 0){       // if child process
        if (execvp(args[0], args) == -1){   // execvp(char* cmd, char* arg[])
            perror("exec");
            exit(111);    
        }
    }
    if (pid > 0){       // parent process
        int statval;
        waitpid(-1, &statval, 0);     // wait for child to be done
        returnStatus = WEXITSTATUS(statval);
        if (returnStatus == 111)
            return false;          // statement did NOT execute
        else
            return true;            // no error in execvp, statement executed 
    }

    return false;
}

bool Command::executeNext(){
    if (connectorType  == "||"){     // logic for "||"
        if (executeCommand())  
            return false;     // statement executed, no need to execute the next command
        return true;          // otherwise, it failed, so execute the next command
    }
    if (connectorType  == "&&"){     // logic for "&&"
        if (executeCommand())  
            return true;     // statement executed, execute the next command
        return false;          // otherwise, it failed, dont execute next command
    }
    if (connectorType  == ";"){     // logic for ";"
        executeCommand();  
        return true;          // next command executes no matter what 
    }
    else
        return false;    // if it doesnt have a connector, it has no next command to execute

}

void Command::showCommand(){
    cout << endl << "arg list: ";
    for (unsigned i = 0; i < cmdStr.size(); i++){
        cout << cmdStr.at(i);
    }
    cout << endl << "connector: " << connectorType << endl;
}
