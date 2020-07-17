#!/bin/bash

echo "Enter a value: "
read a

echo "Enter another value: "
read b

# When assigning variables, no space on either side of the = sign
# To do arithmatic in bash, surround expressions with $(( and ))$

sum=$(( $a + $b ))
echo "The sum of $a + $b is $sum"

diff=$(( $a - $b ))
echo "The difference is $a - $b is $diff"

if [[ $b -ne 0 ]]; then
	div=$(( $a / $b ))
	echo "The division is $a / $b = $div"
else
	echo "Cannot divide"
fi
