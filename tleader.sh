#!/bin/sh

set -e

cd "$1"

while read task
do
    path=$(echo "$1" | sed 's/.//')
    printf "%s" "$path/$task: "

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
