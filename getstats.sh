#!/bin/sh

NHEADERS=$(find . -type d -name "*.h" 2>/dev/null | wc -l)
NTESTS=$(find . -type f -name "tfile" 2>/dev/null | xargs cat | wc -l)

CLOC=$(find . -name "*.c" 2>/dev/null | xargs cat | wc -l)
MAKELOC=$(find . -name "Makefile" 2>/dev/null | xargs cat | wc -l)
SHLOC=$(find . -name "*.sh" 2>/dev/null | xargs cat | wc -l)
PERLLOC=$(find . -name "*.pl" 2>/dev/null | xargs cat | wc -l)

echo "Audited headers: $NHEADERS"
echo "Tests (tfiles) : $NTESTS"
echo

echo "Lines of code:"
printf "\tC   : $CLOC\n"
printf "\tmake: $MAKELOC\n"
printf "\tsh  : $SHLOC\n"
printf "\tPerl: $PERLLOC\n"
