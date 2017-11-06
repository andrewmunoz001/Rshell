#include "cmdComposite.h"

bool cmdLeaf::executeCommand(){
    
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
            return false;
        else
            return true;
        
        }
    return false;
 }



