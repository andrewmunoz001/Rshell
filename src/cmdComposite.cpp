#include "cmdComposite.h"

bool cmdLeaf::executeCommand(){
   
    // check for test
    if (cmdStr.at(0) == "test" || cmdStr.at(0) == "["){
        return test();      // use test function
    }

	unsigned elements = cmdStr.size();
	int returnStatus;
    
    if (cmdStr.size() == 0){
        printf("rshell: Error, No such file or directory\n");
        return false;
    }

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
        if (returnStatus != 0)  //return status will be 0 if executed properly
            return false;
        else
            return true;
        
        }
    return false;
 }

bool cmdLeaf::test(){
    /*  -e   checks if the file/directory exists
        -f  checks if the file/directory exists and is a regular file
        -d  checks if the file/directory exists and is a directory
    */
    char *arg;
    string flag;        // which type of check to perform
    bool exists = false;    // if the file/directory exists
    if (cmdStr.size() > 3){
        printf("rshell: test: Too many arguments\n");
        return false;
    }
    else if (cmdStr.size() == 1){
        printf("rshell: test: No file path entered\n");
        return false;
    }
    else if(cmdStr.size() == 2){    
        arg = (char*)(cmdStr.at(1).c_str());  // convert filename to cstring 
        flag = "-e";     // no flag set, use -e
    } 
    else{
        arg = (char*)(cmdStr.at(2).c_str());
        flag = cmdStr.at(1);
    }
    
    if (flag != "-e" && flag != "-f" && flag != "-d"){  // checks for valid flag
        flag = "-e";        // invalid flag, just check if it exists
     }
    
    struct stat sb;

    if (stat(arg, &sb) == -1) {
        perror("test");
        printf("(False)\n");
        return false;
    } 
   
        exists = true;  // file or directory exists if its made it this far 
    if (flag == "-d" && !(S_ISDIR(sb.st_mode))){
       exists = false; 
    }
    if (flag == "-f" && !(S_ISREG(sb.st_mode))){
        exists = false; 
    }

    if (exists == true){
    printf("(True)\n");
    }
    else{
    printf("(False)\n");
    }
    return exists;    
} 

