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
#include <fcntl.h>
#include <limits.h>	/* for SEM_VALUE_MAX */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define SEMNAME	"/tso"

int main(void)
{
	sem_t *mysem;
	sem_t *mysem2;

	/* Create named semaphore. */
	mysem = sem_open(SEMNAME, O_CREAT | O_EXCL,
			 0777	/* Access mode */,
			 1	/* Initial value */);
	assert(mysem != SEM_FAILED);

	/*
	 * If a process makes multiple successful calls to sem_open() with the
	 * same value for name, the same semaphore address will be returned.
	 */
	mysem2 = sem_open(SEMNAME, O_CREAT);
	assert(mysem2 != SEM_FAILED);
	assert(mysem2 == mysem);

	/* XXX: How do we check against EACCES ? */

	/* O_CREAT and O_EXCL are set and the named semaphore already exists. */
	assert(sem_open(SEMNAME, O_CREAT | O_EXCL) == SEM_FAILED
	    && errno == EEXIST);

	/* Invalid name. */
	assert(sem_open("", O_CREAT | O_EXCL) == SEM_FAILED && errno == EINVAL);

#ifdef SEM_VALUE_MAX
        /*
         * Try to exceed maximum allowed value for semaphore, but first make
         * sure we don't overflow. Otherwise, the value will most likely truncate
         * to 0 and spurious results will be produced.
         */
        if (SEM_VALUE_MAX + 1 > SEM_VALUE_MAX) {
		assert(sem_open(SEMNAME, O_CREAT) == SEM_FAILED
		    && errno == EINVAL);
	}
#endif

	/* O_CREAT is not set and the named semaphore does not exist. */
	assert(sem_open("/thisdefinitelydoesntexist", ~O_CREAT) == SEM_FAILED
	    && errno == ENOENT);

	/* Disassociate from semaphore. */
	assert(sem_close(mysem) == 0);
	assert(sem_close(mysem2) == 0);

	/* Remove semaphore from system. */
	assert(sem_unlink(SEMNAME) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
