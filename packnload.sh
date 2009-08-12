#!/bin/sh

FILENAME=pcca-tests-`date '+%d-%m-%y'`.tar.gz
USERNAME="beket"
HOSTNAME="leaf.dragonflybsd.org"
REMOTEDIR="public_html"

echo ">>> Creating git archive with name $FILENAME"
git archive --format=tar HEAD | gzip > $FILENAME
echo "DONE"

echo ">>> Uploading git archive to $USERNAME@$HOSTNAME/~$REMOTEDIR"
scp "$FILENAME" "$USERNAME@$HOSTNAME:~/$REMOTEDIR"
echo "DONE"
