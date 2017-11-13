#!/bin/bash

echo 'echo TEST 1: && exit' | ../bin/rshell
echo "echo TEST 2: && test ./idontexist || exit" | ../bin/rshell
echo "echo TEST 3: || echo test failed && echo testing... && exit" | ../bin/rshell
echo "echo TEST 4: || idontexist && idontexist; exit" | ../bin/rshell
echo "echo TEST 5: && (echo testing || echo FAILED) && exit" | ../bin/rshell
echo "echo TEST 6: && (((echo testing with nested parenthesis. || echo FAILED) || echo FAILED) && echo testing..); exit" | ../bin/rshell
echo "echo TEST 7: && (echo testing with nests and test cmd && (test ./idontexist || exit))" | ../bin/rshell
echo "echo TEST 8: && echo testing with test cmd && test -d ../bin && exit" | ../bin/rshell
echo "echo TEST 9: && echo testing with test cmd && test -f ../bin/rshell && exit" | ../bin/rshell
echo "echo TEST 10: && echo testing with failed cmd test && [ -d ../bin/rshell ] || exit" | ../bin/rshell
