#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

find . -type f -name "*.h.spec" -exec basename {} \; 2>/dev/null | sort