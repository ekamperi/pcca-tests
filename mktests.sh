#!/bin/sh

usage()
{
    cat <<EOF
Usage: `basename $0` -cbrsmy [directory]
-b    Build tests from sources.
-c    Clean stale files from previous builds.
-h    Print this help message.
-m    Run man pages tests.
-p    Run prototype tests.
-r    Run tests.
-s    Construct sandbox/ directories.
-y    Run symbol tests.
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

    # Create file {read,write}able only by root.
    touch "$1/rootfile600"
    sudo chown root "$1/rootfile600"
    sudo chmod 600 "$1/rootfile600"

    # Create directory {read,write,search}able only by root.
    mkdir "$1/rootdir700"
    sudo chown root "$1/rootdir700"
    sudo chmod 700 "$1/rootdir700"

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
    # Remove old sandbox.
    rm -rf "$1/sandbox"

    # Create new sandbox directory.
    mkdir "$1/sandbox"

    # Populate new sandbox directory with stuff.
    populatesandbox "$1/sandbox"

    echo "Created $1/sandbox directory"
}

buildsandboxes()
{
    # We skip .git/
    for dir in $(find "$1" -name .git -prune -o \
	\( -type d -name "*.h" -print \) 2>/dev/null | sort)
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

    # We skip .git/
    for dir in $(find "$1" -name .git -prune -o \
	\( -type d -name "*.h" -print \) 2>/dev/null | sort)
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

runprototypes()
{
    for dir in $(find "$1" -name .git -prune -o \
	\( -type d -name "*.h" -print \) 2>/dev/null | sort)
    do
	if [ -d "$dir/prototypes" ]; then
	    ./pleader.rb "$dir"
	fi
    done
}

runtests()
{
    # We don't look in directories ending with .h only, as we need to run tests
    # on utilities as well, e.g. utilities/basemame.
    for dir in $(find "$1" \
	\( -name .git -o -name logs -o -name prototypes -o -name sandbox \) \
	-prune -o \( -type d -a ! -name . -print \) 2>/dev/null | sort)
    do
	if [ -f "$dir/tfile" ]; then
	    # Make sure there is no missing sandbox/ directory.
	    if [ -f "$dir/need-sandbox" ] && [ ! -d "$dir/sandbox" ]; then
		echo "WARNING: Missing sandbox/ directory."
		echo "Did you forget to run ./mktests.s -s ?"
		buildsandbox "$dir"
	    fi

	    # All good -- pass control to the test leader script.
	    ./test.rb "$dir"
	fi
    done
}

buildtests()
{
    for dir in $(find "$1" -name .git -prune -o \
	\( -type d -name "*.h" -print \) 2>/dev/null | sort)
    do
	# We save the current directory, so we can step into the target, run
	# 'make' and then return to where we are. We must always cd from the
	# directory where we ran find(1), otherwise the paths returned by it
	# won't be valid.
	OLDPWD=$(pwd)
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

logstatistics()
{
    ./getstats.sh 2>&1 > "$1/stats"

    ./getpassed.sh 2>&1 | grep -v "_prot$" > "$1/functional-passed"
    ./getfailed.sh 2>&1 | grep -v "_prot$" > "$1/functional-failed"

    ./getpassed.sh 2>&1 | grep "_prot$" > "$1/prototypes-passed"
    ./getfailed.sh 2>&1 | grep "_prot$" > "$1/prototypes-failed"

    ./getkilled.sh 2>&1 > "$1/killed"
}

# Parse user supplied arguments.
while getopts "cbrpsmyh" f
do
    case $f in
	b)
	    # Build tests.
	    build=$f
	    ;;
	c)
	    # Clean stale files.
	    clean=$f
	    ;;
	h)
	    # Print a help message.
	    usage
	    ;;
	m)
	    # Run man page tests.
	    manpages=$
	    ;;
	p)
	    # Run prototype tests.
	    prototypes=$
	    ;;
	r)
	    # Run tests.
	    run=$f
	    ;;
	s)
	    # Construct sandobox/ directories.
	    sandbox=$f
	    ;;
	y)
	    # Run symbol tests.
	    symbols=$f
	    ;;
	\?)
	    # Same as before.
	    usage
	    ;;
    esac
done
shift `expr $OPTIND - 1`

# We treat the last (non-option) argument (if any), as the starting path.
# If none is given, we use the current directory as the default one to start
# from.
if [ ! -z $1 ]; then
    STARTDIR=$1
else
    STARTDIR="."
fi

# At least one of -b, -c, -m, -p, -r, -s, -y options must be set.
[ -z "$build"      ] && [ -z "$clean"   ] &&
[ -z "$manpages"   ] && [ -z "$run"     ] &&
[ -z "$sandbox"    ] && [ -z "$symbols" ] &&
[ -z "$prototypes" ] && usage

timestamp=$(date "+%d-%m-%Y.%H:%M:%S")
logdir="logs/$timestamp"
if [ -d "$logdir" ]; then
    echo "The impossible has happened!"
    echo "Log directory: $logdir already exists!"
    exit 1
fi

mkdir -p "$logdir"

# Man page tests.
[ ! -z "$manpages" ] && runmanpages "$STARTDIR" 2>&1 \
    | tee "$logdir/mlinks"

# Symbol tests.
[ ! -z "$symbols" ] && runsymbols "$STARTDIR" 2>&1 \
    | tee "$logdir/symbols"

# Prototype tests.
# They can be executed stand-alone or along with the functional tests.
[ ! -z "$prototypes" ] &&  runprototypes "$STARTDIR" 2>&1 \
    | tee "$logdir/prototypes"

# Build sandboxes.
[ ! -z "$sandbox" ] && buildsandboxes "$STARTDIR" 2>&1 \
    | tee "$logdir/sandboxes"

# Build regular tests.
[ ! -z "$clean"  ] || [ ! -z "$build" ] && buildtests "$STARTDIR" 2>&1 \
    | tee "$logdir/functional-build"

# Run regular tests.
[ ! -z "$run"    ] && runtests "$STARTDIR" 2>&1 \
    | tee "$logdir/functional-run"

# Log statistics
logstatistics "$logdir"
