#!/bin/sh

# This function reads a $header/functions.list file and for every entry there,
# it spawns a man(1) invocation, to determine the availability of the respective
# manual page. It then generates an SQL command to update the appropriate field
# in the database.
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

	    # Unfortunately, solaris's man(1) always return success,
	    # even for a non-reachable man page. So, this can only
	    # produce meaningful results in Linux/BSD hosts.
	    if ! man "$func" >/dev/null 2>/dev/null; then
		echo "UPDATE psx_functions SET man_page = 'no'  WHERE function_name = '$func'"
	    else
		echo "UPDATE psx_functions SET man_page = 'yes' WHERE function_name = '$func'"
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
