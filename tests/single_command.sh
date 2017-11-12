#!/bin/bash

../bin/rshell <<EOF
echo testing 
echo this prints
ls
ps
echo Now exiting...
exit
EOF
