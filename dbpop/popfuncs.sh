#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

# Unless explicitly provided, use .. directory as the default one.
if [ ! -z "$1" ]; then
    STARTDIR="$1"
else
    STARTDIR=".."
fi

# For every given `functions.list' file, generate a set of INSERT records
# to populate the SQL database.
popfunctions()
{
    # First line is always the header.
    {
	read header
	while read func; do
	    # Skip empty lines.
	    if [ -z "$func" ]; then
		continue
	    fi

	    printf "INSERT INTO psx_functions VALUES('$header', '$func', 'pending',"
	    printf " 'pending', 'pending', 'pending', 'pending', 'pending', 'pending');\n"
	done
    } < "$1"
}

# Scan all $header/ directories.
for dir in $(find "$STARTDIR" -name .git -prune -o \
    \( -type d -name "*.h" -print \) 2>/dev/null | sort)
do
    if [ -f "$dir/functions.list" ]
    then
	popfunctions "$dir/functions.list"
    fi
done
