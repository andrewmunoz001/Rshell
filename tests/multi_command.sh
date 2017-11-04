#!/bin/bash

echo 'echo this will print || echo this will not print; exit' | ../bin/rshell
echo 'ls && echo this will print after ls; exit' | ../bin/rshell
echo 'echo Hello, this is rshell || echo this wont print && echo this will print after Hello; exit' | ../bin/rshell
echo 'echo 1 || echo 2 || echo 3 4 5; exit' | ../bin/rshell

