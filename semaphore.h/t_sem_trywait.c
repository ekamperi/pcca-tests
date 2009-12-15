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

int main(void)
{
	sem_t mysem;
	int val = 999;

	/* Create a semaphore. */
	assert(sem_init(&mysem,
		   0 /* not shared between processes */,
		   1 /* semaphore value */) == 0);

	/* Lock semaphore. */
	assert(sem_trywait(&mysem) == 0);

	/*
	 * Make sure the sem value has been lowered to zero or negative.
	 * A negative value represents the number of processes blocked by
	 * us.
	 */
	assert(sem_getvalue(&mysem, &val) == 0);
	assert(val < 0 || val == 0);

	/* This must fail with EAGAIN. */
	assert(sem_trywait(&mysem) == -1 && errno == EAGAIN);

	/* Unlock semaphore. */
	assert(sem_post(&mysem) == 0);

	/* We should be at exactly where we started. */
	assert(sem_getvalue(&mysem, &val) == 0);
	assert(val == 1);

	/* Destroy previous. */
	assert(sem_destroy(&mysem) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
