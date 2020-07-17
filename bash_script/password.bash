#!/bin/bash

secret_code=zoom99

echo -n "Guess the code: "
read code

while [ $secret_code != $code ]; do
	echo "Try Again!"
	read code
done
echo "BINGO!"


# Infinite loop
# while : ; do
# {code}
# done
