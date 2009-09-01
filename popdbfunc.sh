#!/bin/sh

# If no argument is given, print usage.
if [ -z "$1" ]; then
    echo "Usage: $0 /path/to/header/functions.list"
    exit 1
fi

# First line is header.
{
    read header

    while read func; do
	# Skip empty lines.
	if [ -z "$func" ]; then
	    continue
	fi

	manpage="yes"
	if ! man "$func" >/dev/null 2>/dev/null; then
	    manpage="no"
	fi

        printf "INSERT INTO psx_functions VALUES('$header', '$func', 'pending',"
	printf " 'pending', 'pending', 'pending', 'pending', '$manpage', 'pending');\n"
    done
} < "$1"
