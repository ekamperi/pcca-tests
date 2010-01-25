#!/bin/sh

if [ ! -z "$1" ]; then
    DIR="$1"
else
    DIR="."    # Default top level directory to start from.
fi

# Number of audited headers
NHEADERS=$(find "$DIR" -name .git -prune -o \( -type d -name "*.h" -print \) \
    2>/dev/null | wc -l)

# Number of test cases (as found in tfiles)
NTESTS=$(find "$DIR" -name .git -prune -o \( -type f -name "tfile" -print \) \
    2>/dev/null | xargs cat | wc -l)

# Number of assert()'s (as found in .c files)
NASSERTS=$(find "$DIR" -name .git -prune -o \( -name "*.c" -print \) \
    2>/dev/null | xargs grep "assert(" | wc -l)

# Number of lines of code in .c files
CLOC=$(find "$DIR" -name .git -prune -o \( -name "*.c" -print \) 2>/dev/null \
    | xargs cat | wc -l)

# Number of lines of code in Makefiles
MAKELOC=$(find "$DIR" -name .git -prune -o \( -name "Makefile" -print \) \
    2>/dev/null | xargs cat | wc -l)

# Number of lines of code in shell scripts
SHLOC=$(find "$DIR" -name .git -prune -o \( -name "*.sh" -print \) 2>/dev/null \
    | xargs cat | wc -l)

# Number of lines of code in Perl scripts
PERLLOC=$(find "$DIR" -name .git -prune -o \( -name "*.pl" -print \) 2>/dev/null \
    | xargs cat | wc -l)

echo ">>> Headers"
printf "\tAudited: $NHEADERS\n"

echo
echo ">>> Test files"
printf "\ttfiles : $NTESTS\n"
printf "\tasserts: $NASSERTS\n"

echo
echo ">>> Lines of code"
printf "\tC      : $CLOC\n"
printf "\tmake   : $MAKELOC\n"
printf "\tsh     : $SHLOC\n"
printf "\tPerl   : $PERLLOC\n"

# Number of tests that passed
NPASSED=$(find "$DIR" -name .git -prune -o \( -name "log.passed" -print \) \
    2>/dev/null | xargs cat | wc -l)

# Number of tests that failed during runtime
NFAILED_BUILDTIME=$(find "$DIR" -name .git -prune -o \
    \( -name "log.failed-runtime" -print \) 2>/dev/null | xargs cat | wc -l)

# Number of tests that failed to build
NFAILED_RUNTIME=$(find "$DIR" -name .git -prune -o \
    \( -name "log.failed-buildtime" -print \) 2>/dev/null | xargs cat | wc -l)

echo
echo ">>> Results from last run"
printf "\tPassed         : $NPASSED\n"
printf "\tFailed to run  : $NFAILED_BUILDTIME\n"
printf "\tFailed to build: $NFAILED_RUNTIME\n"
