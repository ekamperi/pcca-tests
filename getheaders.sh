#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

find . -type d -name "*.h" 2>/dev/null | sed 's/.\///' | sort
