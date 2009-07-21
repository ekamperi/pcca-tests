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

assert()
{
    if ! $1; then
	echo "Assertion failed: $1, line $2."
	exit 1
    fi
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

if [ -f "$ATPATH/at.allow" ]; then
    if grep $USER "$ATPATH/at.allow" >/dev/null; then
	PRIV=1
    fi
else
    if [ -f "$ATPATH/at.deny" ]; then
	if ! grep $USER "$ATPATH/at.deny" >/dev/null; then
	    PRIV=1
	fi
    fi
fi

# Allow if we are root (although running tests as root, is an awful idea).
[ "$USER" = "root" ] && PRIV=1

# Make sure we are privileged enough.
assert "[ $PRIV -eq 1 ]" $LINENO

# Try to register a job.
# After the submission of a job, at(1) must print to _stderr_ a string of the
# form "job %s at %s\n", at_job_id, <date>". That's why we redirect stderr to
# stdout before pipe-ing grep(1).
OUTPUT=`at -f "$ATJOBS" 00:00 2>&1`
echo "$OUTPUT" | !grep "00:00:00" >/dev/null && exit 1

# Try to remove previous job, but for this we need the at job id.
ATJOBID=`echo "$OUTPUT" | awk '/[Jj]ob*[a-z0-9.]/{ print $2 }' | head -n1`
assert "[ ! -z $ATJOBID ]" $LINENO
at -r "$ATJOBID"

# Done
echo "passed"
