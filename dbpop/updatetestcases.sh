#!/bin/sh

# This function reads a $header/functions.list file and for every entry there,
# it tries to find(1) a test case. It then generates an SQL command to update
# the appropriate field in the database.
scanheader()
{
    {
	# The first line is always the header.
	read header

	while read func; do
	    # Skip empty lines.
	    if [ -z "$func" ]; then
		continue
	    fi

	    # This isn't so efficient; we will revisit it later.
	    # (famous last words)
	    found=$(find ".." -name .git -prune -o \( -type f -name "t_$func.c" \
		-print \) 2>/dev/null )
	    if [ ! -z "$found" ]; then
		echo "UPDATE psx_functions SET test_case = 'yes' WHERE function_name = '$func';"
	    else
		echo "UPDATE psx_functions SET test_case = 'no'  WHERE function_name = '$func';"
	    fi
	done
    } < "$1"
}

# Scan all $header/ directories.
for dir in $(find ".." -name .git -prune -o \( -type d -name "*.h" -print \) \
    2>/dev/null | sort)
do
    if [ -f "$dir/functions.list" ]; then
        scanheader "$dir/functions.list"
    fi
done
