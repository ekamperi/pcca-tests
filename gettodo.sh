#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

for t in $(find . -type f -name TODO 2>/dev/null | sort); do
    echo ">>> $(echo $t | sed 's/.\///')"
    cat "$t"
    echo
done
