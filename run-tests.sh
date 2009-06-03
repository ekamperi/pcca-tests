#!/bin/sh

for dir in `find . -name .git -prune -o -type d -a ! -name . -print`
do
    OLDPWD=`pwd`

    cd "$dir"

    if [ -e "Makefile" ]
    then
	echo `basename $dir`
	make run
    fi
    echo

    cd "$OLDPWD"
done
