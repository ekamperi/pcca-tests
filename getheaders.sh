#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

find . -name .git -prune -o \( -type d -name "*.h" -exec basename {} \; \) \
    2>/dev/null | sort
