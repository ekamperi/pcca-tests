/*
 * Copyright (c) 2009, Stathis Kamperis
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Original idea provided by Nicolas Thery <nthery@gmail.com>.
 */

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int rv;

	/*
	 * Make sure we don't run the test as root. This is a prerequisite.
	 * XXX: Should we print a more user friendly message ?
	 */
	assert(getuid() != 0);

	/*
	 * Make sure that the setuid bit is set and the owner of the binary
	 * is root. This is a prerequisite.
	 * XXX: Should we print a more user friendly message ?
	 */
	assert(geteuid() == 0);

	/*
	 * According to POSIX access() is supposed to use the real user ID in
	 * place of the effective user ID and the real group ID in place of
	 * the effective group ID.
	 * And since we run the test case as a regular user, the following call
	 * should fail. Even though the binary has the setuid bit set and the
	 * owner of it is root.
	 */
	rv = access("sandbox/rootfile600", R_OK);
	assert(rv == -1 && errno == EACCES);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
