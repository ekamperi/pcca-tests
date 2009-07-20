#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

# Enter target directory, where the test cases reside.
cd "$1"

# Every directory with test cases contains a `tfile' listing  which test cases
# are supposed to be run.
while read task
do
    # Skip tfile entries that start with a #.
    if echo "$task" | grep "^#" >/dev/null
    then
        continue
    fi

    # If there is another shell script we are running, let it handle the output
    # on its own.
    if ! echo "$task" | grep ".sh$" >/dev/null
    then
	path=$(echo "$1" | sed 's/.//')
	printf "%s" "$path/$task: "
    fi

    # If we can't find the binary, most likely it failed to build during
    # compilation. We treat this as a failed test case.
    if ! [ -x "$task" ]
    then
	printf "failed (test does not exist)\n"
	continue
    fi

    ./"$task" &
    sleep 0.5

    if jobs -l %+ 2>/dev/null | grep -v -i done >/dev/null
    then
        sleep 10
	if kill -9 $(jobid %+ 2>/dev/null) >/dev/null 2>/dev/null
	then
	     echo "failed (test exceeded run time limit)"
	fi
    fi
done < tfile
