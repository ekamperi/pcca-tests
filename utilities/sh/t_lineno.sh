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

if [ -n "$LINENO" ]; then
    if [ $LINENO -ne 45 ]; then
	echof 'LINENO is affected by comments and/or newlines.'
	echof 'Subsequent output may give false negative results.'
    fi
else
    # This is fatal, as in there is no point in continuing.
    echof 'LINENO built-in var is not implemented.'
    exit 1
fi

# We now check for any side effect of continuation lines.
# Quoting from Issue 6:
#
# "If a <newline> follows the backslash, the shell shall interpret this as
# line continuation. The backslash and <newline>s shall be removed before
# splitting the input into tokens."
echo 'This is the beginning' \
     'of a continuation line.' >/dev/null

if [ $LINENO -ne 64 ]; then
    echof 'LINENO built-in var is affected by continuation lines.'
fi

# Done
[ $FAIL -eq 0 ] && echo "$SCRIPTNAME: passed"
