#!/bin/sh

rundir()
{
    echo "Changing directory to:" `basename $1`
    cd "$1"

    # Run the tests in current directory, if there is a Makefile at all.
    if [ -e "Makefile" ]
    then
	make run
    else
	echo "No tests for current directory."
    fi
    echo

    # Get all directories in the current level and recurse into them.
    for dir in `find . -type d -depth 1 ! -name ".*" 2>&-`
    do
	rundir "$dir"
    done

    cd ..
}

# Fire off!
rundir "."
