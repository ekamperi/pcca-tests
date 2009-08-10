#!/bin/sh

# Number of audited headers
NHEADERS=$(find . -name .git -prune -o \( -type d -name "*.h" -print \) \
    2>/dev/null | wc -l)

# Number of test cases (as found in tfiles)
NTESTS=$(find . -name .git -prune -o \( -type f -name "tfile" -print \) \
    2>/dev/null | xargs cat | wc -l)

# Number of lines of code in .c files
CLOC=$(find . -name .git -prune -o \( -name "*.c" -print \) 2>/dev/null \
    | xargs cat | wc -l)

# Number of lines of code in Makefiles
MAKELOC=$(find . -name .git -prune -o \( -name "Makefile" -print \) \
    2>/dev/null | xargs cat | wc -l)

# Number of lines of code in shell scripts
SHLOC=$(find . -name .git -prune -o \( -name "*.sh" -print \) 2>/dev/null \
    | xargs cat | wc -l)

# Number of lines of code in Perl scripts
PERLLOC=$(find . -name .git -prune -o \( -name "*.pl" -print \) 2>/dev/null \
    | xargs cat | wc -l)

echo ">>> Headers"
printf "\tAudited: $NHEADERS\n"

echo
echo ">>> Test files"
printf "\ttfiles : $NTESTS\n"

echo
echo ">>> Lines of code"
printf "\tC      : $CLOC\n"
printf "\tmake   : $MAKELOC\n"
printf "\tsh     : $SHLOC\n"
printf "\tPerl   : $PERLLOC\n"

# Number of tests that passed
NPASSED=$(find . -name .git -prune -o \( -name "log.passed" -print \) \
    2>/dev/null | xargs cat | wc -l)

# Number of tests that failed
NFAILED=$(find . -name .git -prune -o \( -name "log.failed" -print \) \
    2>/dev/null | xargs cat | wc -l)

echo
echo ">>> Results from last run"
printf "\tPassed : $NPASSED\n"
printf "\tFailed : $NFAILED\n"
