#!/bin/sh

usage()
{
    printf "Usage: %s: [-c] [-b] [-r]\n" \
        `basename $0` >&2
    printf -- "-c\tClean stale files from previous builds.\n"
    printf -- "-b\tBuild tests from sources.\n"
    printf -- "-r\tRun tests.\n"
    printf -- "-h\tPrint this help message.\n"
    printf    "At least one of the above options must be specified.\n"
    exit 1
}

runtests()
{
    if [ ! -f "tlreader" ]
    then
	cc tleader.c -o tleader
    fi

    find . -name .git -prune -o -type d -a ! -name . -exec ./tleader.sh {} \;
}

buildtests()
{
    for dir in `find . -name .git -prune -o -type d -a ! -name . -print`
    do
	OLDPWD=`pwd`

	cd "$dir"

	if [ -f "Makefile" ]
	then
	    if [ ! -z "$clean" ]
	    then
		make clean
	    fi
	    make
	fi

	cd "$OLDPWD"
    done
}

# Parse user supplied arguments
while getopts "cbrh" f
do
    case $f in
        c)
            clean=$f
            ;;
	b)
	    build=$f
	    ;;
	r)
	    run=$f
	    ;;
        h)
            usage
            ;;
        \?)
            usage
            ;;
    esac
done
shift `expr $OPTIND - 1`

# At least one of -c, -b, -r options must be set.
[ -z "$clean" ] && [ -z "$build" ] && [ -z "$run" ] && usage

# Fire!
[ ! -z "$build" ] && buildtests
[ ! -z "$run" ] && runtests
