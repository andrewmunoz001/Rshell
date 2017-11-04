#!/bin/bash

echo 'exit' | ./bin/rshell
echo 'echo this will print then exit; exit' | ./bin/rshell
echo 'echo this prints 1st && echo this prints 2nd, then exits && exit' | ./bin/rshell

