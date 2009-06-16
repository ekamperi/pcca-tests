#!/bin/sh

filename=pcca-tests-`date '+%d-%m-%y'`.tar.gz

printf "Creating git archive with name $filename... "
git archive --format=tar HEAD | gzip > $filename
printf "DONE\n"

printf "Uploading git archive to leaf.dragonflybsd.org/~public_html... "
scp $filename beket@leaf.dragonflybsd.org:~/public_html
printf "DONE\n"
