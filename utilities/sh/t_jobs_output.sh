#!/bin/sh
#
# Copyright (c) 2009, Stathis Kamperis
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
# COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
# OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.

# The name of the script (i know, but it should work ok for our use).
SCRIPTNAME=$(basename "$0")

# This is the default exit status. Zero (0) signifies 'pass'.
FAIL=0

echof()
{
    echo "$SCRIPTNAME: $1"

    # By default, variables referenced from within a function,
    # refer to the global namespace, unless the 'local' keyword
    # is prepended to them.
    FAIL=1
}

sleep 20 &

# Output when neither -p nor -l is given to jobs
# Format: [%d] %c %s %s\n", <job-number>, <current>, <state>, <command>
rv=$(jobs)
if [ ! $? -eq 0 ]; then
    echof 'jobs fatal error (should not happen)'
    exit 1	# fatal
else
    # Job number
    #rv="[123] running sleep    10"
    rv2=$(echo "$rv" | awk '$1 ~ /^\[[+-]?[0-9]+\]$/ { print $1 }')
    if [ -z "$rv2" ]; then
	echof 'format violated in <job number>'
    fi

    # Current (maybe space or + or -)
    rv2=$(echo "$rv" | awk '$2 ~ /[+-]+|[a-zA-z]+/ { print $2 }')
    if [ -z "$rv2" ]; then
	echof 'format violated in <current>'
    fi

    # State
    rv2=$(echo "$rv" | awk '/[ \t]+[Rr]unning[ \t]+/ { print }')
    if [ -z "$rv2" ]; then
	echof 'format violated in <state>'
    fi

    # Command
    rv2=$(echo "$rv" | awk '/[ \t]+sleep[ \t]+10[ \t]*/ { print }')
    if [ -z "$rv2" ]; then
	echof 'format violated in <command>'
    fi
fi

# Make sure -p is supported (mandatory)
rv=$(jobs -p)
if [ ! $? -eq 0 ]; then
    echof 'jobs -p not supported'
else
    # XXX: Is it possible for process IDs to be non numerical ?
    # We also are a bit relaxed on leading/trailing whitespace.
    rv2=$(echo "$rv" | awk '/^[ \t]*[+-]?[0-9]+[ \t]*$/ { print $1 }')
    if [ -z "$rv2" ]; then
	echof 'jobs -p format: "%d\n", <process ID> violated'
    fi
fi

# Make sure -l is supported (mandatory)
rv=$(jobs -l)
if [ ! $? -eq 0 ]; then
    echof 'jobs -l not supported'

    # XXX: Should we bother checking jobs -l output ?
    # It should be pretty much the same as jobs, except for the new 'process
    # group ID' field or so.
fi


# Done
[ $FAIL -eq 0 ] && echo "$SCRIPTNAME: passed"
