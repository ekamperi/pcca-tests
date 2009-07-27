#!/bin/sh

echo ">>> Missing utilities maybe implemented as built-in shell functions."
echo

while read util
do
    if [ -z $(whereis -b $util | awk '{print $2}') ]; then
	echo "Possibly missing utility: $util"
    fi
done < util.list
