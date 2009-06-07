#!/bin/sh

set -e

cd "$1"

while read task
do
    path=$(echo "$1" | sed 's/.//')
    printf "$path/$task: "

    if ! [ -x "$task" ]
    then
	echo "failed (test does not exist)"
	continue
    fi

    ./"$task"
done < tfile
