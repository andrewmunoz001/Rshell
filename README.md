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

As of assignment 4 our shell now has these features:
1) The ability to redirect input and output
2) The ability to append to an existing file
3) The ability to pipe multiple programs
4) The ability to use all of the above mentioned features, together.

Here is an example: 
```c++

rshell $ cat < input | grep "word" | wc > output

/* What this code does, is redirect the input of whatever is inside the file named 
"input" and redirects it to the cat program. After that, a pipe is used to search for 
the word "word". Another pipe is used to get the word count of that result, 
then finally, the output of all of that combined is sent to the file named "output". */


```

## How our program works

A main issue with our last program was that we used a queue to handle commands, which worked fine for a few commands, but as the connectors added up the output was unpredictable.
This program takes full advantage of composite design in order to build our "Command Tree". A single command and multiple commands that are connected by a connector are both treated the same but have different implementations. Commands that are connected with a || or && are going to behave differently, but they both "execute". 

Our method of building our command tree was through using recursion. After a user inputs a string, it gets parsed into a vector of strings, which can be arguments or connectors or parenthesis. After the string gets parsed, the command tree is built by recursively creating command leaf objects from the end of the vector until it reaches the beginning of the vector. The method is made a bit more clear by viewing the turnToBase function that is inside Parse.cpp.


## List of known bugs:

1) The main bug found during testing was a memory leak that occurs when using the "exit" command. The way memory is freed is that when the Parse object goes out of scope in shell.cpp, the destructor gets called. This desctructor then deletes all space allocated for the commandTree pointer in Parse.h. However, if a user inputs "exit", this parse object never goes out of scope, and the memory doesn't get deallocated. However, when the program is just looping, getting user input, there does not appear to be a memory leak.

2) Some input leads to undefined behavior, such as if the user only input "]". This leads to the program crashing with a Segmentation fault.

3) Multiple output redirection doesn't perform in the correct way. For example, in bash ls > a > b > c, will have files a and b be empty, and file c have all the output. However in our program, all of the output will be in file a, with files b and c being empty.
