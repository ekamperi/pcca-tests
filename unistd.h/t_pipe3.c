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
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <openssl/sha.h>

#define MAX_BLOCKS	 3000	/* Number of blocks to transmit over pipe */
#define MAX_DATALEN	32768	/* Maximum length of transmitted data */
#define MAX_PAIRS	   10	/* Number of thread pairs transmitting data */

/* Each couple of threads communicates over a single 'private' pipe. */
int fd[MAX_PAIRS][2];

/* This data structure is written/read across the pipe boundary. */
struct block {
	char          b_sha[41];		/* SHA hash */
	unsigned char b_data[MAX_DATALEN];	/* Data payload */
	unsigned int  b_len;			/* Data lenghth */
};

/* Function prototypes. */
static void *readerthr(void *arg);
static void *writerthr(void *arg);

int main(void)
{
	pthread_t tid[2*MAX_PAIRS];	/* Reader and writer thread */
	int i, idx[2*MAX_PAIRS];

	/* Initialize random number generator. */
	srand(time(NULL));

	/*
	 * Create the pipes.
	 *
	 * fd[i][0] is the read end.
	 * fd[1][1] is the write end.
	 */
	for (i = 0; i < MAX_PAIRS; i++)
		assert(pipe(fd[i]) != -1);

	/* Create the indexes. */
	for (i = 0; i < 2*MAX_PAIRS; i++)
		idx[i] = i/2;

	/* Create the reader threads. */
	for (i = 0; i < 2*MAX_PAIRS; i+=2)
		assert(pthread_create(&tid[i], NULL, readerthr, &idx[i]) == 0);

	/*
	 * Ideally we would have a barrier here, so that all reader threads
	 * are created before any writer thread does. Otherwise, a SIGPIPE
	 * signal could kill us.
	 */
	sleep(1);

	/* Create the writer threads. */
	for (i = 1; i < 2*MAX_PAIRS; i+=2)
		assert(pthread_create(&tid[i], NULL, writerthr, &idx[i]) == 0);

	/* Wait for the writer threads to complete. */
	for (i = 0; i < 2*MAX_PAIRS; i+=2)
		assert(pthread_join(tid[i], NULL) == 0);

	/* Wait for the reader threads to complete. */
	for (i = 1; i < 2*MAX_PAIRS; i+=2)
		assert(pthread_join(tid[i], NULL) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
readerthr(void *arg)
{
	int idx, i;
	ssize_t bytesread, rv;
	struct block myblock;

	/* Get the number of pipe we will be reading from. */
	idx = *(int *)arg;

	for (i = 0; i < MAX_BLOCKS; i++) {
		/* Read block from pipe. */
		bytesread = 0;
		do {
			rv = read(fd[idx][0], (char *)&myblock + bytesread,
			    sizeof(myblock) - bytesread);
			assert(rv != -1);
			bytesread += rv;
		} while(bytesread < sizeof(myblock));

		/* A little bit paranoid. */
		assert(bytesread == sizeof(myblock));

		/*
		 * Re-calculate the SHA hash and compare it with the old
		 * one.
		 */
		char newsha[41];

		SHA1(myblock.b_data, myblock.b_len, newsha);
		assert(memcmp(newsha, myblock.b_sha, SHA_DIGEST_LENGTH) == 0);
	}

	pthread_exit(NULL);
}

static void *
writerthr(void *arg)
{
	int idx, rndfd, i;
	struct block myblock;

	/* Get the number of pipe we will be writing to. */
	idx = *(int *)arg;

	/* Open /dev/urandom. */
	rndfd = open("/dev/urandom", O_RDONLY);
	assert(rndfd != -1);

	for (i = 0; i < MAX_BLOCKS; i++) {
		/* Calculate block size. */
		myblock.b_len = 1 + rand() % (MAX_DATALEN-1);

		/*
		 * Read random data.
		 * XXX: Should we trust read(2) to provide us with all
		 * the data we want, in one single call ?
		 */
		assert(read(rndfd, myblock.b_data, myblock.b_len)
		    == myblock.b_len);

		/* Calculate the SHA hash and pack it in the struct .*/
		SHA1(myblock.b_data, myblock.b_len, myblock.b_sha);

		/* Write block to pipe. */
		assert(write(fd[idx][1], &myblock, sizeof(myblock))
		       == sizeof(myblock));
	}

	/* We no longer need /dev/urandom. */
	assert(close(rndfd) != -1);

	pthread_exit(NULL);
}
