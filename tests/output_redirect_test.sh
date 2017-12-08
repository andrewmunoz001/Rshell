#!/bin/bash

../bin/rshell <<EOF
echo "***** Starting Tests *****"
mkdir otests
echo A > ./otests/test1
echo B > ./otests/test1
echo "This is testing output redirection" > ./otests/test3
exit
EOF
