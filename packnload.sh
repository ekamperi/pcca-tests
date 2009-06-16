#!/bin/sh

FILENAME=pcca-tests-`date '+%d-%m-%y'`.tar.gz

printf "Creating git archive with name $FILENAME... "
git archive --format=tar HEAD | gzip > $FILENAME
printf "DONE\n"

printf "Uploading git archive to leaf.dragonflybsd.org/~public_html... "
scp $FILENAME beket@leaf.dragonflybsd.org:~/public_html
printf "DONE\n"
