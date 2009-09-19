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
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	mode_t oldmode, oldmode2, oldmode3;

#if defined(S_IRWXU) && defined(S_IRWXG) && defined(S_IRWXO)
	/* Set the file creation mask. */
	oldmode = umask(S_IRWXU | S_IRWXG | S_IRWXO);

	/* Restore the original creation mask. */
	oldmode2 = umask(oldmode);

	/*
	 * After this, oldmode3 must be equal to the very original
	 * creation mask.
	 */
	oldmode3 = umask(oldmode);

	assert(oldmode2 == (S_IRWXU | S_IRWXG | S_IRWXO));
	assert(oldmode3 == oldmode);

	/*
	 * XXX: We should add tests to check whether creation mask is _actually_
	 * honoured by at least: open(), creat(), mkdir(), mkfifo() and
	 * optionally mknod(), mq_open(), sem_open().
	 */

	printf("passed\n");
#else
	printf("passed (critical: umask modification skipped)\n");
#endif

	return (EXIT_SUCCESS);
}
