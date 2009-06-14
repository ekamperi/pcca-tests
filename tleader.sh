#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

# Enter target directory, where the test cases reside.
cd "$1"

# Every directory with test cases contains a `tfile' listing  which test cases
# are supposed to be run.
while read task
do
    path=$(echo "$1" | sed 's/.//')
    printf "%s" "$path/$task: "

    # If we can't find the binary, most likely it failed to build during
    # compilation. We treat this as a failed test case.
    if ! [ -x "$task" ]
    then
	printf "failed (test does not exist)\n"
	continue
    fi

    ./"$task" &
    sleep 0.2

    if jobs -l %+ >/dev/null 2>/dev/null
    then
        sleep 5
	if kill -9 $(jobid %+ 2>/dev/null) >/dev/null 2>/dev/null
	then
	     echo "failed (test exceeded run time limit)"
	fi
    fi
done < tfile
