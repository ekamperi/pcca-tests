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
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(void)
{
	/* Create a semaphore. */
	sem_t mysem;

	assert(sem_init(&mysem,
		   0 /* not shared between processes */,
		   1 /* semaphore value */) == 0);

	/* Invalid timeout and the lock can be acquired immediately. */
        struct timespec now, timeout;

	timeout.tv_sec  = 0;
	timeout.tv_nsec = -1;
	assert(sem_timedwait(&mysem, &timeout) != -1);
	assert(sem_post(&mysem) != -1);

	timeout.tv_sec  = 0;
	timeout.tv_nsec = 1000*1000*1000+1;
	assert(sem_timedwait(&mysem, &timeout) != -1);
	/* We intentionally don't unlock the semaphore here! */

	/* Invalid timeout and the lock cannot be acquired immediately. */
	timeout.tv_sec  = 0;
	timeout.tv_nsec = -1;

	assert(sem_timedwait(&mysem, &timeout) == -1 && errno == EINVAL);

	/* Valid timeout and the lock cannot be acquired immediately. */
	assert(clock_gettime(CLOCK_REALTIME, &now) == 0);
	timeout.tv_sec  = now.tv_sec + 2;
	timeout.tv_nsec = now.tv_nsec;
	assert(sem_timedwait(&mysem, &timeout) == -1 && errno == ETIMEDOUT);

	/* Cleanup. */
	assert(sem_destroy(&mysem) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
