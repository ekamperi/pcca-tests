#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

find . -name .git -prune -o \( -type d -name "*.h" -print \) 2>/dev/null \
    | xargs basename | sort
