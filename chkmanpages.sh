#!/bin/sh

# If no argument is given, print usage.
if [ -z "$1" ]; then
    echo "Usage: $0 path/to/headers/functions.list"
    exit 1
fi

# First line is header, second is whitespace.
{
    read header
    read foobar

    while read func; do
	if ! man $func >/dev/null 2>/dev/null; then
	    echo "Possibly missing man page for: $header/$func"
	fi
    done
} < "$1"
