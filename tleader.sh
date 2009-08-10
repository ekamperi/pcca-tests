#!/usr/pkg/bin/bash

# Exit immediately if any untested command fails in non-interactive mode.
set -e

# Enter target directory, where the test cases reside.
cd "$1"

# Remove log files from previous runs.
LOGPASSED="log.passed"
LOGFAILED="log.failed"

rm -f "$LOGPASSED" 2>/dev/null
rm -f "$LOGFAILED" 2>/dev/null

# Every directory with test cases contains a `tfile' listing  which test cases
# are supposed to be run. The entries of this file are basically the names
# of the executables.
while read task
do
    # Skip `tfile' entries that start with a #.
    if echo "$task" | grep "^#" >/dev/null
    then
        continue
    fi

    # If there is another shell script we are running, let it handle the output
    # on its own. For example unistd.h/uleader.sh.
    if ! echo "$task" | grep "\.sh$" >/dev/null
    then
	path=$(echo "$1" | sed 's/.//')
	printf "%s" "$path/$task: "
    fi

    # If we can't find the binary, most likely it failed to build during
    # compilation. We treat this as a failed test case.
    if [ ! -x "$task" ]
    then
	printf "failed (test does not exist)\n"
	echo "$task" >> "$LOGFAILED"
	continue
    fi

    "./$task" &
    pid=$!	# The process ID of the most recent background command
                # executed from the current shell. We need it in case
                # the test goes wild and need must kill it.
    sleep 0.2

    cnt=0
    while jobs -l %+ >/dev/null 2>/dev/null
    do
        sleep 0.5
	cnt=$((cnt+1))

	if [ $cnt -ge 20 ]; then
	    if kill -9 "$pid" 2>/dev/null
	    then
		echo "failed (test exceeded run time limit)"
		echo "$task" >> "$LOGFAILED"
		break	# Don't trust job control, just break now, here.
	    fi
	fi
    done

    if wait $pid; then
	echo "$task" >> "$LOGPASSED"
    else
	echo "$task" >> "$LOGFAILED"
    fi
done < tfile

