#!/bin/bash

#List
names=(Windsor Toronto Ottawa)

echo ${names[0]} ${names[1]} ${names[2]}
echo ${names[@]:1:2}  # Two elements starting from index 1
echo ${names[*]}  # All elements
echo ${#names[@]}  # Number of elements

names=(${names[@]} London)  # Add a new element
names[1]=Quebec
echo ${names[*]}
