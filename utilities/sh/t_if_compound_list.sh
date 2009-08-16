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

TESTFILE="./t_if_compound_list_test"
rm -f "$TESTFILE"	# Paranoia

# Quoting from Issue 6:
#                  ;
# compound_list    :              term
#                  | newline_list term
#                  |              term separator
#                  | newline_list term separator
#                  ;
# if_clause        : If compound_list Then compound_list else_part Fi
#                  | If compound_list Then compound_list           Fi
#                  ;
# else_part        : Elif compound_list Then else_part
#                  | Else compound_list
#                  ;
cat > "$TESTFILE" <<'EOF'
   if true; then
   else
   fi
   echo fail
EOF

rv=$(/bin/sh "$TESTFILE" 2>/dev/null)
if [ ! -z "$rv" ]; then
    echof 'null compound list encountered in if clause'
fi
rm -f "$TESTFILE"

# Done
[ $FAIL -eq 0 ] && echo "$SCRIPTNAME: passed"
