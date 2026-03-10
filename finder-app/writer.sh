#!/bin/bash

writefile=$1
writestr=$2

if [ -z "$writefile" ] || [ -z "$writestr" ]
then
	echo "Error: Please provide writefile and writestr arguments"
	exit 1
fi

mkdir -p $(dirname "$writefile")

echo "$writestr" > "$writefile"

if ! echo "$writestr" > "$writefile"
then
	echo "Error: Could not create file $writefile"
	exit 1
fi
