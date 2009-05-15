#!/bin/sh

filename=pcca-tests-`date '+%d-%m-%y'`.tar.gz
git archive --format=tar HEAD | gzip > $filename
scp $filename beket@leaf.dragonflybsd.org:~/public_html
