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
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	TOTALSIZE	(1 << 15)
#define	BUFSIZE		(1 << 10)

#define	MAGICBYTE_A	(0xAB)
#define MAGICBYTE_B	(0xCD)

unsigned char buf[BUFSIZE];

sem_t sem_freebytes_buf1;
sem_t sem_freebytes_buf2;
sem_t sem_writtenbytes_buf1;
sem_t sem_writtenbytes_buf2;

/* Function prototypes. */
static void *writer1(void *arg);
static void *writer2(void *arg);
static void *reader(void *arg);

int
main(void)
{
	pthread_t wr1, wr2, rd;

	/* Initialize semaphores. */
	assert(sem_init(&sem_freebytes_buf1,
		   0 /* not shared between processes */,
		   BUFSIZE/2 /* semaphore value */) == 0);

	assert(sem_init(&sem_freebytes_buf2,
		   0 /* not shared between processes */,
		   BUFSIZE/2 /* semaphore value */) == 0);

        assert(sem_init(&sem_writtenbytes_buf1,
                   0 /* not shared between processes */,
                   0 /* semaphore value */) == 0);

        assert(sem_init(&sem_writtenbytes_buf2,
                   0 /* not shared between processes */,
                   0 /* semaphore value */) == 0);

	/* Create threads. */
	assert(pthread_create(&wr1, NULL, writer1, (void *)NULL) == 0);
	assert(pthread_create(&wr2, NULL, writer2, (void *)NULL) == 0);
	assert(pthread_create(&rd, NULL, reader, (void *)NULL) == 0);

	/* Wait until threads complete. */
	assert(pthread_join(wr1, NULL) == 0);
	assert(pthread_join(wr2, NULL) == 0);
	assert(pthread_join(rd, NULL) == 0);

	/* Cleanup. */
	assert(sem_destroy(&sem_freebytes_buf1) == 0);
	assert(sem_destroy(&sem_freebytes_buf2) == 0);
        assert(sem_destroy(&sem_writtenbytes_buf1) == 0);
        assert(sem_destroy(&sem_writtenbytes_buf2) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
writer1(void *arg)
{
	size_t i, pos;

	for (i = 0; i < TOTALSIZE; i++) {
		/* Calculate position in buffer. */
		pos = i % (BUFSIZE/2);

		assert(sem_wait(&sem_freebytes_buf1) == 0);
		buf[pos] = MAGICBYTE_A;
		/*printf("writer1: pos: %d byte: %d\n", pos, buf[pos]);*/
		assert(sem_post(&sem_writtenbytes_buf1) == 0);
	}

	pthread_exit(NULL);
}

static void *
writer2(void *arg)
{
	size_t i, pos;

	for (i = 0; i < TOTALSIZE; i++) {
		/* Calculate position in buffer. */
		pos = BUFSIZE/2 + (i % (BUFSIZE/2));

                assert(sem_wait(&sem_freebytes_buf2) == 0);
                buf[pos] = MAGICBYTE_B;
		/*printf("writer2: pos: %d byte: %d\n", pos, buf[pos]);*/
                assert(sem_post(&sem_writtenbytes_buf2) == 0);
	}

	pthread_exit(NULL);
}

static void *
reader(void *arg)
{
	size_t i, pos;

	for (i = 0; i < 2*TOTALSIZE; i++) {
		/* Calculate position in buffer. */
		pos = i % BUFSIZE;

		/* Are we in the first half part? */
		if (pos < BUFSIZE/2) {
			assert(sem_wait(&sem_writtenbytes_buf1) == 0);
			assert(buf[pos] == MAGICBYTE_A);
			/*printf("reader:  pos: %d byte: %d\n", pos, buf[pos]);*/
			sem_post(&sem_freebytes_buf1);
		}
		/* ... or the second half ? */
		else {
			sem_wait(&sem_writtenbytes_buf2);
			assert(buf[pos] == MAGICBYTE_B);
			/*printf("reader:  pos: %d byte: %d\n", pos, buf[pos]);*/
			sem_post(&sem_freebytes_buf2);
		}
	}

	pthread_exit(NULL);
}
