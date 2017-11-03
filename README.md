##RSHELL-PICO-DE-GALLO


Welcome to our program!

This program is designed to be a command shell, similar to the shell thats in every linux distro! 
The main functions of the program are as follows:
1) Prints a command prompt (rshell $)
2) Reads in a command on one line
3) Handles a connector ( || or && or ; )
4) Performs execution of an executable based on that connector
5) Has its own "exit" command to exit the shell
6) Any input after a # is treated as a comment


**Stuff to add in the future**

The main goal is to get our program to use a design pattern. Our program looks like it needs to implement composite design as soon as possible, in order to handle executables. Since our program does NOT implement any design patterns, there are some peculiar bugs, which shall be explained in the list below.


## List of known bugs:

1) When multiple connectors are used they are not handled properly. For example, the command "ls || ls || ls || ls" should only output one ls command. However, ours executes this twice. This is why we need to implement composite design. Multiple commands would be treated as a single bool variable on if it executed or not, and the multiple ls problem would be fixed.

2) Similar to the problem described above. Connectors operate perfectly when there are only two commands. However any more commands than that and it will not perform the desired combination of commands. 

3) If a command with incorrect parameters is inputted, for example "ls ps", then the command is treated as though it was correctly executed. ls ps || ls   should output ls, since ls ps fails. However since ls ps is treated as though it was correctly executed ls does not output.

