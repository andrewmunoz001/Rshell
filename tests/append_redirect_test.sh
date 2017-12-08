#!/bin/bash

../bin/rshell <<EOF
echo "***** Starting Tests *****"
rm -rf aptests
mkdir aptests 
echo These >> ./aptests/test
echo "Should all be on" >> ./aptests/test
echo "Seperate lines :)" >> ./aptests/test
echo "Testing if piping works with append..." >> ./aptests/test
ls | wc >> ./aptests/test
echo "It does :)" >> ./aptests/test
echo "****** Done testing, check folder 'aptests'"

exit
EOF
