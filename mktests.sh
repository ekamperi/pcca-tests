#!/bin/sh

STARTDIR="."	# Default top level directory to start from when running tests.

usage()
{
    cat <<EOF
Usage: `basename $0` -cbrsmy [directory]
-c    Clean stale files from previous builds.
-b    Build tests from sources.
-r    Run tests.
-s    Construct sandbox/ directories.
-m    Run man pages tests.
-y    Run symbol tests.
-h    Print this help message.
At least one of the above options must be specified.
EOF

    exit 1
}

populatesandbox()
{
    # Create unresolvable symbolic links.
    ln -s "infloop2" "$1/infloop"
    ln -s "infloop" "$1/infloop2"

    # Create file with full permissions.
    touch "$1/file777"
    chmod 0777 "$1/file777"

    # Create file without execute permissions.
    touch "$1/file666"
    chmod 0666 "$1/file666"

    # Create file without write permissions.
    touch "$1/file555"
    chmod 0555 "$1/file555"

    # Create regular loop to file.
    ln -s "file777" "$1/fileloop"

    # Create file with zero permissions.
    touch "$1/file000"
    chmod 0000 "$1/file000"

    # Creat file {read,write}able only by root.
    touch "$1/rootfile600"
    sudo chown root "$1/rootfile600"
    sudo chmod 600 "$1/rootfile600"

    # Create directory with full permissions.
    mkdir "$1/dir777"
    chmod 0777 "$1/dir777"

    # Create regular loop to directory.
    ln -s "dir777" "$1/dirloop"

    # Create directory with zero permissions.
    mkdir "$1/dir000"
    chmod 0000 "$1/dir000"

    # Create directory without execute/search permission.
    mkdir "$1/dir666"
    chmod 0666 "$1/dir666"

    # Create directory without write permission.
    mkdir "$1/dir555"
    chmod 0555 "$1/dir555"

    # Create file that it's not a directory.
    touch "$1/notadir"
    chmod 777 "$1/notadir"

    # Create file that it's not a tty.
    touch "$1/notatty"
    chmod 777 "$1/notatty"

    # Create FIFO special file.
    mkfifo "$1/fifo"
    chmod 777 "$1/fifo"
}

buildsandbox()
{
    # XXX: Fix permissions or else we won't be able to delete it.
    chmod 777 "$dir/sandbox/dir000" 2>/dev/null
    chmod 777 "$dir/sandbox/zeropermdir" 2>/dev/null

    # Remove old sandbox.
    rm -rf "$dir/sandbox"

    # Create new sandbox directory.
    mkdir "$dir/sandbox"

    # Populate new sandbox directory with stuff.
    populatesandbox "$dir/sandbox"

    echo "Created $dir/sandbox directory"
}

buildsandboxes()
{
    # We skip .git/objects/* subdirectories.
    for dir in $(find "$1" -name .git -prune -o -type d -name "*.h" \
	2>/dev/null | sort)
    do
	if [ -f "$dir/need-sandbox" ]; then
	    buildsandbox "$dir"
	fi
    done
}

runmanpages()
{
    echo 'A missing man page may be due to a missing MLINK' \
	 'or an unimplemented function.'
    echo

    # We skip .git/objects/* subdirectories.
    for dir in $(find "$1" -name .git -prune -o -type d -name "*.h" 2>/dev/null \
	| sort)
    do
	if [ -f "$dir/functions.list" ]; then
	    ./chkmanpages.sh "$dir/functions.list"
	fi
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
    # We skip the .git/objects/* subdirectories.
    # We don't look for directories ending with .h only, as we also need to run
    # tests on utilities as well, e.g. utilities/basemame.

    for dir in $(find "$1" -name .git -prune -o -type d -a ! -name . \
	2>/dev/null | sort)
    do
	if [ -f "$dir/tfile" ]; then
	    # Make sure there is no missing sandbox/ directory.
	    if [ -f "$dir/need-sandbox" ] && [ ! -d "$dir/sandbox" ]; then
		echo "WARNING: Missing sandbox/ directory."
		echo "Did you forget to run ./mktests.s -s ?"
		buildsandbox "$dir"
	    fi

	    # All good -- pass control to the test leader script.
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
	if [ -f "Makefile" ]; then
	    if [ ! -z "$clean" ]; then
		make clean >/dev/null
	    fi

	    if [ ! -z "$build" ]; then
		# Continue processing after errors (only for targets that aren't
		# affected). There's nothing to worry about tests that fail to
		# compile. This normally means that the host misses some stuff.
		# So we treat an uncompilable test case, as a failed test case.
		#
		# Mind that -k is actually an option mandated by POSIX, so we
		# can use it safely (as in blame others, if they don't support
		# it).
		make -k
	    fi
	fi

	# Go back to where we were.
	cd "$OLDPWD"
    done
}

# Parse user supplied arguments.
while getopts "cbrsmyh" f
do
    case $f in
	c)
	    # Clean stale files.
	    clean=$f
	    ;;
	b)
	    # Build tests.
	    build=$f
	    ;;
	r)
	    # Run tests.
	    run=$f
	    ;;
	s)
	    # Construct sandobox/ directories.
	    sandbox=$f
	    ;;
	m)
	    # Run man page tests.
	    manpages=$
	    ;;
	y)
	    # Run symbol tests.
	    symbols=$f
	    ;;
	h)
	    # Print a help message.
	    usage
	    ;;
	\?)
	    # Same as before.
	    usage
	    ;;
    esac
done
shift `expr $OPTIND - 1`

# We treat the last (non-option) argument (if any), to be the starting path.
if [ ! -z $1 ]
then
    STARTDIR=$1
fi

# At least one of -c, -b, -r, -s, -m, -y options must be set.
[ -z "$clean"    ] && [ -z "$build"   ] &&
[ -z "$run"      ] && [ -z "$sandbox" ] &&
[ -z "$manpages" ] && [ -z "$symbols" ] && usage

# Man page tests.
[ ! -z "$manpages" ] && runmanpages "$STARTDIR"

# Symbol tests.
[ ! -z "$symbols" ] && runsymbols "$STARTDIR"

# Fire!
[ ! -z "$sandbox" ] && buildsandboxes "$STARTDIR"
[ ! -z "$clean"  ] || [ ! -z "$build" ] && buildtests "$STARTDIR"
[ ! -z "$run"    ] && runtests "$STARTDIR"
