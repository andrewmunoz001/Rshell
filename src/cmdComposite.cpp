#include "cmdComposite.h"

bool cmdLeaf::executeCommand(int fdin, int fdout){
   
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
        if (dup2(fdin, 0) == -1){
            perror("dup");
            exit(1);
        }
        if (dup2(fdout, 1) == -1){
            perror("dup");
            exit(1);
        }
        if (execvp(args[0], args) == -1){   // execvp(char* cmd, char* arg[])
            perror("execvp");
            //delete [] args;       // this doesnt even do anything
            exit(111);        
        }   
    }   
    if (pid > 0){       // parent process
        delete [] args;
        int statval;
        waitpid(pid, &statval, 0);     // wait for child to be done
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

/*     **** PIPE DEFINITION ****    */

pipeConnector::pipeConnector(cmdBase *l, cmdBase *r) : redirect(l, r)
{}

bool pipeConnector::executeCommand(int fdin, int fdout){
    /*  execute left side of pipe   */
	int p[2];
    bool ret = false;
	pipe(p);	

    if (left->executeCommand(fdin, p[1])){
	    close(p[1]);
	    ret = right->executeCommand(p[0], fdout );
    }
	close(p[0]);
    return ret;
}

/*  **** REDIRECTION DEFINITIONS **** */

/*                          ***** "<" *****                             */
inputConnector::inputConnector(cmdBase *l, cmdBase *r) : redirect(l,r){
}

bool inputConnector::executeCommand(int fdin, int fdout){
	int input;
    input = open((char*)(right->getfile()).c_str(), O_RDONLY);
    if (input < 0){ 
        perror("Input");
        return false;
    } 
	return left->executeCommand(input, fdout);
}


/*                      ***** ">" *****                              */
outputConnector::outputConnector(cmdBase *l, cmdBase *r) : redirect(l,r){
}

bool outputConnector::executeCommand(int fdin, int fdout){
    
    bool ret;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;    // sets permissions
    int output = open((char*)(right->getfile()).c_str(), O_WRONLY | O_CREAT | O_TRUNC, mode);      
    // opens the file
    if (output < 0){ 
        perror("Output");
        return false;
    }   

    ret = left->executeCommand(fdin, output);
    close(output);
    return ret;
}


/*                  ***** ">>" *****                                */
appendConnector::appendConnector(cmdBase *l, cmdBase *r) : redirect(l,r){
}

bool appendConnector::executeCommand(int fdin, int fdout){
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;    // sets permissions
    int output = open((char*)(right->getfile()).c_str(), 
    O_WRONLY | O_APPEND | O_CREAT , mode);      
    // opens the file
    if (output < 0){ 
        perror("Open file");
        return false;
    }   
 
    return left->executeCommand(fdin, output);
}


