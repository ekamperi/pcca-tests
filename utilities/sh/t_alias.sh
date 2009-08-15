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

# Quoting from Issue 6:
#
# If the value of the alias replacing the word ends in a <blank>, the shell
# shall check the next command word for alias substitution; this process shall
# continue until a word is found that is not a valid alias or an alias value
# does not end in a <blank>.

TESTFILE="./t_alias_test"
rm -f "$TESTFILE"	# Paranoia

#
# TEST 1: 1 space in the first alias
#
cat > "$TESTFILE" <<'EOF'
    alias f='for ' s='i in'
    f s pass; do echo $i; done
EOF
rv=$(/bin/sh "$TESTFILE" 2>/dev/null)
if [ "$rv" != "pass" ]; then
    echof "1 space in first alias ignored"
    exit 1	# Fatal
fi
rm -f "$TESTFILE"


#
# TEST 2: 1 space in both aliases
#
cat > "$TESTFILE" <<'EOF'
    alias f='for ' s='i in '
    f s pass; do echo $i; done
EOF
rv=$(/bin/sh "$TESTFILE" 2>/dev/null)
if [ "$rv" != "pass" ]; then
    echof "1 space in both aliases ignored"
fi
rm -f "$TESTFILE"


#
# TEST 3: >1 space in the first alias
#
cat > "$TESTFILE" <<'EOF'
    alias f='for   ' s='i in'
    f s pass; do echo $i; done
EOF
rv=$(/bin/sh "$TESTFILE" 2>/dev/null)
if [ "$rv" != "pass" ]; then
    echof "1> space in the first alias ignored"
fi
rm -f "$TESTFILE"


#
# TEST 4: >1space in both aliases
#
cat > "$TESTFILE" <<'EOF'
    alias f='for   ' s='i in    '
    f s pass; do echo $i; done
EOF
rv=$(/bin/sh "$TESTFILE" 2>/dev/null)
if [ "$rv" != "pass" ]; then
    echof "1> space in both aliases ignored"
fi
rm -f "$TESTFILE"

# Done
[ $FAIL -eq 0 ] && echo "$SCRIPTNAME: passed"
