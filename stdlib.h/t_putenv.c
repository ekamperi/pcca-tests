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
 */

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

int main(void)
{
	char buf[BUFSIZE + 1];  /* Reserve space for '\0' */

	/*
	 * The following are all extensions to the standard,
	 * but they are good for an implementation to have
	 * them. Mind that putenv() has been changed to take
	 * char * as argument, so we can't supply string
	 * literals safely.
	 */

	/* String doesn't contain an ``='' character . */
	strncpy(buf, "foo", BUFSIZE);
	assert(putenv(buf) == -1 && errno == EINVAL);

	/* ``='' is the first character of string. */
	strncpy(buf, "=123", BUFSIZE);
	assert(putenv(buf) == -1 && errno == EINVAL);

	strncpy(buf, "=", BUFSIZE);
	assert(putenv(buf) == -1 && errno == EINVAL);

        /* String is a NULL pointer. */
        assert(putenv(NULL) == -1 && errno == EINVAL);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
