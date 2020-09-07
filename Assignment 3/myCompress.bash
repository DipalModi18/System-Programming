#!/bin/bash  

target_directory="$(pwd)"

usage() { echo "USAGE: myCompress [-t target-directory] extension-list"; 1>&2; exit 1; }

while getopts t: option
do
	case "${option}"
		in
		t) target_directory=${OPTARG};;
		*) usage;
	esac
done

echo "Target Directory: $target_directory"

shift $((OPTIND-1)) # OPTIND gives the position of the next command line argument.
# shift n: removes n strings from the positional parameters list. 
# Thus shift $((OPTIND-1)) removes all the options that have been parsed by getopts from the parameters list

if [[ $# == 0 ]]; then 
	echo "Please provide extensions for the files to be compressed";
	usage;
	exit;
fi

echo "Compressing files with extensions: $*"

for ext in "$@"; do
	found=false;
	list_files=`ls $target_directory | grep .*."$ext"`;
	for file in $list_files; do
		found=true
		gzip "$target_directory/$file"; 
	done
	if [ "$found" = false ]; then
		echo "No files with extension $ext in the $target_directory";
	fi
done

