#!/bin/sh

NHEADERS=$(find . -type d -name "*.h" 2>/dev/null | wc -l)
NTESTS=$(find . -type f -name "tfile" 2>/dev/null | xargs cat | wc -l)

CLOC=$(find . -name "*.c" 2>/dev/null | xargs cat | wc -l)
MAKELOC=$(find . -name "Makefile" 2>/dev/null | xargs cat | wc -l)
SHLOC=$(find . -name "*.sh" 2>/dev/null | xargs cat | wc -l)
PERLLOC=$(find . -name "*.pl" 2>/dev/null | xargs cat | wc -l)

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

NPASSED=$(find . -name "log.passed" 2>/dev/null | xargs cat | wc -l)
NFAILED=$(find . -name "log.failed" 2>/dev/null | xargs cat | wc -l)

echo
echo ">>> Results from last run"
printf "\tPassed : $NPASSED\n"
printf "\tFailed : $NFAILED\n"
