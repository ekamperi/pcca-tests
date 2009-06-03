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
    # Ignore .git/ (sub)directories.
    for dir in `find . -name .git -prune -o -type d -a ! -name . -print`
    do
	rundir "$dir"
    done

    # Make sure we backtrack as well once we are done with a directory.
    cd ..
}

# Fire off!
rundir "."
