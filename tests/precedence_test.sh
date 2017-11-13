#!/bin/bash

../bin/rshell <<EOF
echo **********Testing precedence operator, no nesting**********
echo **********This will also test the connectors from assignment 2**********
echo
echo TEST 1: && (echo A && echo B) || (echo C && echo D) && echo TEST 1 SUCCESS 
echo
echo TEST 2: && (idontexist || idontexist) || (echo TEST 2 && echo SUCCESSFUL)
echo
echo TEST 3: && (echo TEST 3 || echo FAILED) && (echo SUCCESSFUL || echo FAILED)
echo
echo TEST 4: && (echo 1 || echo FAILED); (echo 2 || echo FAILED)
echo
echo TEST 5: && (idontexist || echo test) || (echo FAILED || echo FAILED) && echo TEST 5 SUCCESS 
echo
echo TEST 6: && (idontexist || idontexist) && (echo TEST FAILED || echo TEST FAILED) || echo TEST 6 SUCCESS
echo
echo **********Testing precedence operator WITH nesting**********
echo
echo TEST 1: && ((( echo testing... || echo FAILED ) && echo testing...) || echo TEST FAILED) && echo TEST 1 SUCCESS
echo TEST 2: && (echo testing.. && (echo testing... || (echo FAILED || echo FAILED))) && echo TEST 2 SUCCESS
echo TEST 3: && (((idontexist || idontexist) || idontexist) || idont exist) && echo TEST 3 FAILED || echo TEST 3 SUCCESS
echo TEST 4: && ((echo A && echo B) || (echo FAILED || echo FAILED)) && echo TEST 4 SUCCESS || echo TEST 4 FAILED
echo TEST 5: && ((idontexist && echo FAILED) || (echo testing.. || echo FAILED)) && echo TEST 5 SUCCESS || echo TEST 5 FAILED
echo
echo **********Testing precedence operator with the TEST command**********
echo TEST 1: && (test ./precedence_test.sh || echo TEST FAILED) && echo TEST 1 SUCCESS || echo TEST 1 FAILED
echo TEST 2: && ([ ./precedence_test.sh ] || echo TEST FAILED) && echo TEST 2 SUCCESS || echo TEST 2 FAILED
echo TEST 3: && (test -d ./precedence_test.sh || echo testing..) && echo TEST 3 SUCCESS || echo TEST 3 FAILED
echo TEST 4: && ([-d ./precedence_test.sh ] || echo testing...) && echo TEST 4 SUCCESS || echo TEST 4 FAILED
echo **********Testing nested precedence operator with TEST command**********
echo TEST 1: && (([ ./precedence_test.sh ] || echo FAILED) && echo testing...) || echo TEST 1 FAILED &&  echo TEST 1 SUCCESS
echo TEST 2: && (([ idontexist ] && echo FAILED) || echo testing.....) || echo TEST 2 FAILED && echo TEST 2 SUCCESS
echo TEST 3: && ( echo testing... && (test -e ./precedence_test.sh || echo FAILED) || (echo FAILED && echo FAILED) ) && echo TEST 3 SUCCESS

echo *****************TESTING EMPTY PARENTHESIS AND UNEVEN PARENTHESIS********************
echo TEST 1: && () || () && (); () && echo TEST 1 FAILED || echo TEST 1 SUCCESS
echo TEST 2: && ((echo uneven parentheses) ; echo none of this should execute
echo If above is invalid input, TEST 2 SUCCESSFUL
echo TEST 3: )))) && echo this shouldnt execute
echo If above is invalid input, TEST 3 SUCESSFUL
echo TEST 4: Lets try breaking our program && () () (); () || (    ) && echo TEST FAILED || echo TEST 4 SUCCESSFUL 
echo TEST 5: && [] || [] && [] && echo TEST 5 FAILED || echo TEST 5 SUCCESSFUL
exit
EOF
