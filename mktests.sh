#!/bin/sh

STARTDIR="."	# top level directory to start from when running tests

usage()
{
    cat <<EOF
Usage: `basename $0` -cbrs [directory]
-c    Clean stale files from previous builds.
-b    Build tests from sources.
-r    Run tests.
-s    Construct sandboxes.
-y    Run symbols' tests.
-h    Print this help message.
At least one of the above options must be specified.
EOF

    exit 1
}

populatesandbox()
{
    # Create unresolvable symbolic links
    ln -s "loop2" "$1/loop"
    ln -s "loop" "$1/loop2"

    # Create file with zero permissions
    touch "$1/zeroperm"
    chmod 0000 "$1/zeroperm"

    # Create directory with zero permissions
    mkdir "$1/zeropermdir"
    chmod 0000 "$1/zeropermdir"

    # Create file that it's not a directory
    touch "$1/notadir"
    chmod 777 "$1/notadir"

    # Create file that it's not a tty
    touch "$1/notatty"
    chmod 777 "$1/notatty"
}

buildsandboxes()
{
    for dir in `find "$1" -type d -name "*.h"`
      do
      if [ -f "$dir/need-sandbox" ]
	  then
          # Remove old sandbox
	  rm -rf "$dir/sandbox"

	  # Create sandbox directory
	  mkdir "$dir/sandbox"

	  # Populate sandbox directory with stuff
	  populatesandbox "$dir/sandbox"
      fi
    done
}

runsymbols()
{
    find . -type f -name "*.h.spec" -exec ./symgen.pl --less {} \; 2>/dev/null
}

runtests()
{
    for dir in `find "$1" -name .git -prune -o -type d -a ! -name .`
    do
	if [ -f "$dir/tfile" ]
	then
	    ./tleader.sh "$dir"
	fi
    done
}

buildtests()
{
    for dir in `find "$1" -name .git -prune -o -type d -a ! -name .`
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
		# Continue processing after errors (only for targets that
		# aren't affected).
		make -k
	    fi
	fi

	cd "$OLDPWD"
    done
}

# Parse user supplied arguments
while getopts "cbrsyh" f
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
	s)
	    sandbox=$f
	    ;;
	y)
	    symbols=$f
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

if [ ! -z $1 ]
then
    STARTDIR=$1
fi

# At least one of -c, -b, -r, -s, -y options must be set.
[ -z "$clean"   ] && [ -z "$build"   ] &&
[ -z "$run"     ] && [ -z "$sandbox" ] &&
[ -z "$symbols" ] && usage

# Symbols' tests
[ ! -z "$symbols" ] && runsymbols

# Fire!
[ ! -z "sandbox" ] && buildsandboxes "$STARTDIR"
[ ! -z "$clean"  ] || [ ! -z "$build" ] && buildtests "$STARTDIR"
[ ! -z "$run"    ] && runtests "$STARTDIR"
