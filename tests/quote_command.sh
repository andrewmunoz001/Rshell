#!/bin/bash

../bin/rshell <<EOF
echo "None of these tests should actually print the quote character"
echo "It should print whats inside the quotes, including # and other special chars"
echo "Testing with quotes" 
echo "Testing with # in quotes" 
echo "Testing with ()||&& and # in quotes. This should all still print"
echo "Testing with # after the quotes stop" && #### || echo If this prints, test failed
exit
EOF
