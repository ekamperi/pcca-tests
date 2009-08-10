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

# Issue 7 of the POSIX standard states that the directory where at.{allow, deny}
# files are expected to be, is implementation defined. Eg, in Solaris 10 it's in
# /usr/lib/cron/, whereas in {DragonFly, Net}BSD in /var/at/.
ATPATH="/var/at"

# The file where at(1) reads the jobs from, rather than standard input.
ATJOBS="at.jobs"

# Who are we? Where do we come from? What happens after death?
USER=`who am i | awk '{ print $1 }'`

# We are only allowed to manipulate at-jobs, if there is an `at.allow' file and
# we are listed in it, or if there is an `at.deny' file and we aren't listed it
# it. It is unclear whether `at.allow' takes precedence over `at.deny' when a
# username is contained in both files.
PRIV=0

# We use -r operand because the file may exist, but we may not be able to read it.
# Eg, in NetBSD /var/at/at.* have 600 permissions.
if [ -r "$ATPATH/at.allow" ]; then
    if grep $USER "$ATPATH/at.allow" >/dev/null; then
	PRIV=1
    fi
else
    if [ -r "$ATPATH/at.deny" ]; then
	if ! grep $USER "$ATPATH/at.deny" >/dev/null; then
	    PRIV=1
	fi
    fi
fi

# Allow if we are root (although running tests as root, is an awful idea).
[ "$USER" = "root" ] && PRIV=1

# Make sure we are privileged enough.
if  [ ! $PRIV -eq 1 ]; then
    echo "$0: We are not (or we couldn't determine if we are) privileged enough."
    exit 1
fi

# Try to register a job.
# After the submission of a job, at(1) must print to _stderr_ a string of the
# form "job %s at %s\n", at_job_id, <date>". That said, we redirect stderr to
# stdout before pipe-ing grep(1).
OUTPUT=`at -f "$ATJOBS" 00:00 2>&1`
echo "$OUTPUT" | grep -q "00:00:00"
if [ ! $? -eq 0 ]; then
    echof 'Job datetime is not printed in stderr upon job submission.'
fi

# Extract the at-job id as we will need it later.
ATJOBID=`echo "$OUTPUT" | awk '/[Jj]ob*[a-z0-9.]/{ print $2 }' | head -n1`

# By default at-jobs are scheduled in `a' queue.
if ! at -l -q a | grep -q "$ATJOBID"; then
    echof "Job $ATJOBID wasn't put in 'a' queue."
fi

# Try to remove previous job.
if [ ! -z $ATJOBID ]; then
    at -r "$ATJOBID"
else
    echof 'Job id is not printed in stderr upon job submission.'
fi

# Done
[ $FAIL -eq 0 ] && echo "$SCRIPTNAME: passed"
