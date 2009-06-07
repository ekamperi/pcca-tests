#!/bin/sh

set -e

cd "$1"

while read task
do
    path=$(echo "$1" | sed 's/.//')
    printf "%s" "$path/$task: "

    if ! [ -x "$task" ]
    then
	echo "failed (test does not exist)"
	continue
    fi

    ./"$task" &
    sleep 0.2

    if jobs -s %+ >/dev/null 2>/dev/null
    then
        sleep 1
	echo "failed (test exceeded run time limit)"
	kill -9 $(jobid %+ 2>/dev/null) >/dev/null 2>/dev/null
    fi
done < tfile
