#!/bin/sh

# Exit immediately if any untested command fails in non-interactive mode.
set -e

find . -name "$1" -exec cat {}/tfile \;
