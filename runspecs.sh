#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

find . -type f -name "*.h.spec" -exec ./symgen.pl --less {} \; 2>/dev/null
