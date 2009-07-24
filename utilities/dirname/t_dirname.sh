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

# This is the default exit status. Zero (0) signifies 'pass'.
FAIL=0

echof()
{
    echo "$0: $1"

    # By default, variables referenced from within a function,
    # refer to the global namespace, unless the 'local' keyword
    # is prepended to them.
    FAIL=1
}

# If string consists entirely of slash characters, the result is
# a single slash character.
if [ ! "$(dirname /)" = '/' ] || [ ! "$(dirname //)" = '/' ]; then
    echof 'Single slash character should be returned.'
fi

# If string is // it is implementation defined whether the following apply:
# - If there are any trailing <slash> characters in string, they shall be
#   removed.
# - If the remaining string is empty, string shall be set to a single <slash>
#   character.
if [ ! "$(dirname //)" = '/' ] && [ ! "$(dirname //)" = '//' ]; then
    echof 'dirname on // should yield either / or //'.
fi

# If there are any trailing <slash> characters in string, they shall be
# removed.
if [ ! "$(dirname /foo/bar/)" = "$(dirname /foo/bar)" ]; then
    echof 'Trailing slash characters should be removed.'
fi

# If there are no slash characters in string, string shall be set to a
# single <period> character.
if [ ! "$(dirname foo)" = '.' ]; then
    echof 'Period should be returned for empty string.'
fi

# A few other examples taken from Issue 7.
if [ ! "$(dirname /foo)" = '/' ]; then
    echof 'dirname on /foo should yield /.'
fi

if [ ! "$(dirname /foo/bar)" = '/foo' ]; then
    echof 'dirname on /foo/bar should yield /foo.';
fi

if [ ! "$(dirname foo/bar)" = 'foo' ]; then
    echof 'dirname on foo/bar should yield foo.';
fi

# Done
[ $FAIL -eq 0 ] && echo 'passed'
