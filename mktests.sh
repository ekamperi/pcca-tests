#!/bin/sh

STARTDIR="."	# top level directory to start from when running tests

usage()
{
    cat <<EOF
Usage: `basename $0` -cbrsmy [directory]
-c    Clean stale files from previous builds.
-b    Build tests from sources.
-r    Run tests.
-s    Construct sandboxes.
-m    Run man pages' tests.
-y    Run symbols' tests.
-h    Print this help message.
At least one of the above options must be specified.
EOF

    exit 1
}

populatesandbox()
{
    # Create unresolvable symbolic links
    ln -s "infloop2" "$1/infloop"
    ln -s "infloop" "$1/infloop2"

    # Create file with full permissions
    touch "$1/file777"
    chmod 0777 "$1/file777"

    # Create regular loop to file
    ln -s "file777" "$1/fileloop"

    # Create file with zero permissions
    touch "$1/file000"
    chmod 0000 "$1/file000"

    # Create directory with full permissions
    mkdir "$1/dir777"
    chmod 0777 "$1/dir777"

    # Create regular loop to directory
    ln -s "dir777" "$1/dirloop"

    # Create directory with zero permissions
    mkdir "$1/dir000"
    chmod 0000 "$1/dir000"

    # Create directory without execute/search permission
    mkdir "$1/dir666"
    chmod 0666 "$1/dir666"

    # Create directory without write permission
    mkdir "$1/dir555"
    chmod 0555 "$1/dir555"

    # Create file that it's not a directory
    touch "$1/notadir"
    chmod 777 "$1/notadir"

    # Create file that it's not a tty
    touch "$1/notatty"
    chmod 777 "$1/notatty"

    # Create FIFO special file
    mkfifo "$1/fifo"
    chmod 777 "$1/fifo"
}

buildsandboxes()
{
    for dir in `find "$1" -type d -name "*.h" 2>/dev/null`
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

runmanpages()
{
    echo 'A missing man page may be due to a missing MLINK' \
         'or an unimplemented function.'
    echo
    for f in $(find "$1" -type f -name "functions.list" 2>/dev/null | sort); do
	./chkmanpages.sh "$f"
    done
}

runsymbols()
{
    # For every spec file in tree, we call symgen.pl script. At the moment,
    # we only check for missing symbols (i.e., not checking against leaking
    # symbols).
    #
    # Since the generated C file from symgen.pl may fail to compile
    # (due to a missing header of the host, for instance), we redirect
    # the stderr to /dev/null. We don't care for those errors.

    for f in $(find "$1" -type f -name "*.h.spec" 2>/dev/null | sort); do
	./symgen.pl --less "$f" 2>/dev/null
    done
}

runtests()
{
    # We really need to skip the .git/objects/* subdirectories.
    # Also we don't look for directories ending with .h only, as we may later
    # need to run tests on utilities as well, e.g. utilities/basemame.

    for dir in $(find "$1" -name .git -prune -o -type d -a ! -name . \
	2>/dev/null | sort)
    do
	if [ -f "$dir/tfile" ]
	then
	    ./tleader.sh "$dir"
	fi
    done
}

buildtests()
{
    for dir in $(find "$1" -name .git -prune -o -type d -a ! -name . \
	2>/dev/null | sort)
    do
	# We save the current directory, so we can step into the target,
	# run 'make' and then return to were we are. We must always cd
	# from the directory where we ran find(1), otherwise the paths
	# returned by it won't be valid.
	OLDPWD=`pwd`
	cd "$dir" 2>/dev/null

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
		# aren't affected). This is actually an option mandated
		# by POSIX, so we can use it safely.
		make -k
	    fi
	fi

	# Restore to where we were.
	cd "$OLDPWD"
    done
}

# Parse user supplied arguments
while getopts "cbrsmyh" f
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
	m)
	    manpages=$
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

# At least one of -c, -b, -r, -s, -m, -y options must be set.
[ -z "$clean"    ] && [ -z "$build"   ] &&
[ -z "$run"      ] && [ -z "$sandbox" ] &&
[ -z "$manpages" ] && [ -z "$symbols" ] && usage

# Man pages' tests
[ ! -z "$manpages" ] && runmanpages "$STARTDIR"

# Symbols' tests
[ ! -z "$symbols" ] && runsymbols "$STARTDIR"

# Fire!
[ ! -z "$sandbox" ] && buildsandboxes "$STARTDIR"
[ ! -z "$clean"  ] || [ ! -z "$build" ] && buildtests "$STARTDIR"
[ ! -z "$run"    ] && runtests "$STARTDIR"
