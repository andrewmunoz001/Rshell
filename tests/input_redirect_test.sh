#!/bin/bash

../bin/rshell <<EOF

echo "Test 1: wc < ../Makefile"
wc < ../Makefile
echo "Test 2: grep all < ../Makefile"
grep all < ../Makefile
echo "Test 3: wc < input_redirect_test.sh"
wc < input_redirect_test.sh
echo "Test 4: checking if input redirection works with pipes"
cat < ../Makefile | wc

exit
EOF
