## RSHELL-PICO-DE-GALLO


Welcome to our program!

This program is designed to be a command shell, similar to the shell thats in every linux distro! 
The main functions of the program are as follows:
1) Prints a command prompt (rshell $)
2) Reads in a command on one line
3) Handles a connector ( || or && or ; )
4) Performs execution of an executable based on that connector
5) Has its own "exit" command to exit the shell
6) Any input after a # is treated as a comment

As of assignment 3 our shell now has these features:
1) The ability to test if a file exists. This is used with either "test (flag) (filename)" or "[ (flag) (filename) ]" formats. There are 3 flags the user can input: -e, which checks if the file or directory exists. -f, which checks if the file/directory exists and is a regular file. -d, which checks if the file/directory exists and is a directory. If the user does not specify a flag, the -e flag is used by default.
2) Using the test command (in either format) prints out "(True)" or "(False)", depending on the result of the test.
3) Precedence operators are now supported, also with support for nested operations. For example: 

```c++

rshell $ echo A && echo B || echo C && echo D

output: A
B
D

rshell $ (echo A && echo B) || (echo C && echo D)

output: A
B

//For nested parenthesis:

rshell & (echo 1 && (echo 2 || echo 3) && echo 4) || echo 5

output: 1
2
4

```

## How our program works

A main issue with our last program was that we used a queue to handle commands, which worked fine for a few commands, but as the connectors added up the output was unpredictable.
This program takes full advantage of composite design in order to build our "Command Tree". A single command and multiple commands that are connected by a connector are both treated the same but have different implementations. Commands that are connected with a || or && are going to behave differently, but they both "execute". 

Our method of building our command tree was through using recursion. After a user inputs a string, it gets parsed into a vector of strings, which can be arguments or connectors or parenthesis. After the string gets parsed, the command tree is built by recursively creating command leaf objects from the end of the vector until it reaches the beginning of the vector. The method is made a bit more clear by viewing the turnToBase function that is inside Parse.cpp.


## List of known bugs:

1) The main bug found during testing was a memory leak that occurs when using the "exit" command. The way memory is freed is that when the Parse object goes out of scope in shell.cpp, the destructor gets called. This desctructor then deletes all space allocated for the commandTree pointer in Parse.h. However, if a user inputs "exit", this parse object never goes out of scope, and the memory doesn't get deallocated. However, when the program is just looping, getting user input, there does not appear to be a memory leak.

2) Some input leads to undefined behavior, such as if the user only input "]". This leads to the program crashing with a Segmentation fault.


