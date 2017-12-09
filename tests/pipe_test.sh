#!/bin/bash

../bin/rshell <<EOF
echo "*****     Normal Piping Tests     *****"
echo "Test 1: ls | grep pipe"
ls | grep pipe 
echo "Test 2: ps | grep rshell"
ps | grep rshell
echo "Test 3: ls -a | grep command | sort"
ls -a | grep command | sort

echo "****** Tests with an invalid pipe command"
echo "Test 1: ls | idontexist || echo TEST SUCCESS"
ls | idontexist || echo TEST SUCCESS
echo "Test 2:  idontexist | grep | sort || echo TEST SUCCESS"
idontexist | grep pipe | sort || echo TEST SUCESS
echo "Test 3: cat pipe_test.sh | sort | idontexist || TEST SUCCESS"
cat pipe_test.sh | sort | idontexist || echo TEST SUCCESS

echo "***** Tests with multiple pipes   *****"
echo "Test 1: ls | grep pipe | tr a-z A-Z"
ls | grep pipe | tr a-z A-Z
echo "Test 2: ls | grep pipe | wc"
ls | grep pipe | wc

echo "***** Tests that implement everything   ******"
rm -rf pipetest
mkdir pipetest

echo "Test 1: cat < pipe_test.sh | grep pipe | sort | tr a-z A-Z > ./pipetest/test1output"
cat < pipe_test.sh | grep pipe | sort | tr a-z A-Z > ./pipetest/test1output
echo "Test 2: ls | tr a-z A-Z | wc > ./pipetest/test2output"
ls | tr a-z A-Z | wc > ./pipetest/test2output

exit
EOF
