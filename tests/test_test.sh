#!/bin/bash

../bin/rshell <<EOF
echo *****Now testing using test and -e, -d, and -f flags*****
echo
echo E FLAG TEST: && test -e ../Makefile && echo Test 1 successful || echo TEST 1 FAILED
echo D FLAG TEST: && test -d ../bin && echo Test 2 successful || echo TEST 2 FAILED
echo F FLAG TEST: && test -f ../bin && echo TEST 3 FAILED || echo Test 3 successful
echo **********Testing "test" using too many arguments**********
echo
echo TEST 1: && test too many args && echo TEST 1 FAILED || echo test 1 successful
echo TEST 2: && test -a too many args && echo TEST 2 FAILED || echo test 2 successful
echo TEST 3: && [ too many args ] && echo TEST 3 FAILED || echo test 3 successful
echo **********Testing "test" using too few arguments**********
echo
echo TEST 1: && test && echo TEST 1 FAILED || echo test 1 successful 
echo TEST 2: && [  ] && echo TEST 2 FAILED || echo test 2 successful
echo *****Testing "test" using no flag, this should automatically set the e flag*****
echo
echo TEST 1: && test ../Makefile && echo Test 1 successful || echo TEST 1 FAILED
echo TEST 2: && test ../bin && echo Test 2 successful || echo TEST 2 FAILED
echo TEST 3: && [ ../bin ] && echo Test 3 successful || echo TEST 3 FAILED 
echo TEST 4: && [ ../Makefile ] && echo Test 4 successful || echo TEST 4 FAILED
echo TEST 5: && [ ../idontexist ] && echo TEST 5 FAILED || echo Test 5 successful
echo **********Testing using connectors from assignment 2************
test idontexist || echo Or connector test SUCCESSFUL
test ./test_test.sh && echo And connector test SUCCESSFUL
[ idontexist ] || echo Or Connector test 2 SUCCESSFUL
[ ./test_test.sh ] && echo And Connector Test 2 SUCCESSFUL
test idontexist; echo semiconnector test SUCCESSFUL
test ./test_test.sh; echo semiconnector test 2 SUCCESSFUL
[ idontexist ]; echo semiconnector test 3 SUCCESSFUL
[ ./test_test.sh ]; echo semiconnector test 4 SUCCESSFUL
exit
EOF
