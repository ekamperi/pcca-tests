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
    echo $1

    # By default, variables referenced from within a function,
    # refer to the global namespace, unless the 'local' keyword
    # is prepended to them.
    FAIL=1
}

# If string consists entirely of slash characters, the result is
# a single slash character.
if [ ! "$(basename /)" = '/' ] || [ ! "$(basename //)" = '/' ]; then
    echof 'Single slash character should be returned.'
fi

# If there are any trailing slash characters in string, they should
# be removed.
if [ ! "$(basename /foo/bar/)"  = 'bar' ] ||
   [ ! "$(basename /foo/bar//)" = 'bar' ]; then
    echof 'Trailing slashes should be removed.'
fi

# If there are any slash characters remaining in string, the prefix
# of string up to and including the last slash character in string
# shall be removed.
if [ ! "$(basename foo/bar)"     = 'bar' ] ||
   [ ! "$(basename foo/foo/bar)" = 'bar' ]; then
    echof 'Prefix of string up to and including slash character'
          'should be removed.'
fi

# If suffix is not identical to the characters remaining in string,
# and is identical to a suffix of the characters remaining in string,
# the suffix should be removed from string.
if [ ! "$(basename /foo/bar/lala lala)" = 'lala' ]; then
    echof 'If suffix is identical to remaining string, it should not'
          'be removed.'
fi

if [ ! "$(basename /foo/bar/lala la)" = 'la' ]; then
    echof 'Suffix should be removed.'
fi

# Not finding suffix, shouldn't be considered an error.
if [ ! $(basename /foo/bar lala) ]; then
    echof 'Not finding suffix, should not be considered an error.'
fi

# Done
[ $FAIL -eq 0 ] && echo 'passed'
