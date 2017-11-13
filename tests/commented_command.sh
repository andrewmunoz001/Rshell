#!/bin/bash

../bin/rshell <<EOF
echo Test 1 # echo ERROR || echo NONE OF THIS SHOULD PRINT 
echo Test 2 # [ ./commented_command.sh ] && echo THIS SHOULDNT PRINT 
echo Test 3 # (echo this shouldnt print && echo and this shouldnt); echo this still wont
echo Test 4 && (echo still testing comments || ps) && # this shouldnt even try to execute
echo Test 5 && # echo TEST FAILED
echo Test 6 && echo testing... # || echo FAILED
echo **********Testing when a comment is middle of precedence operator or test cmd*******
echo Test 1: && (echo # this doesnt print || echo same)
echo If above is invalid input, Test 1 successful
echo Test 2: && test # ./commented_command.sh
echo If above didnt break program, Test 2 successful
echo Test 3: && # test ./commented_command.sh
echo If above didnt break program, Test 3 successful
echo Test 4: && (echo testing... || echo FAILED) && # echo this doesnt execute
echo If above didnt break program, Test 4 successful
exit
EOF
