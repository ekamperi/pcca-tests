#!/bin/sh

usage()
{
    cat <<EOF
Usage: `basename $0` -cbr
-c    Clean stale files from previous builds.
-b    Build tests from sources.
-r    Run tests.
-h    Print this help message.
At least one of the above options must be specified.
EOF

    exit 1
}

runtests()
{
    for dir in `find . -name .git -prune -o -type d -a ! -name .`
    do
	if [ -f "$dir/tfile" ]
	then
	    ./tleader.sh "$dir"
	fi
    done
}

buildtests()
{
    for dir in `find . -name .git -prune -o -type d -a ! -name . -print`
    do
	OLDPWD=`pwd`

	cd "$dir"

	# Tests must come with a Makefile.
	if [ -f "Makefile" ]
	then
	    if [ ! -z "$clean" ]
	    then
		make clean >/dev/null
	    fi

	    if [ ! -z "$build" ]
	    then
		make
	    fi
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
[ ! -z "$clean" ] || [ ! -z "$build" ] && buildtests
[ ! -z "$run" ] && runtests
