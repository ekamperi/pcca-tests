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

/*
  Before going on, let me dedicate you this excellent song:

  How many roads must a man walk down,
  before you call him a man?

  Yes, 'n' how many seas must a white dove sail,
  before she sleeps in the sand?

  Yes, 'n' how many times must the cannon balls fly,
  before they're forever banned?

  The answer, my friend, is blowin' in the wind;
  the answer is blowin' in the wind.

  BLOWIN' IN THE WIND (Bob Dylan, 1963)
*/

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <openssl/sha.h>

#define MAX_BLOCKS	10000	/* Number of blocks to transmit over pipe */
#define MAX_DATALEN	32768	/* Maximum length of transmitted data */

struct {
	char          b_sha[41];		/* SHA hash */
	unsigned char b_data[MAX_DATALEN];	/* Data payload */
	unsigned int  b_len;			/* Data lenghth */
} block;

int main(void)
{
	int fd[2];
	pid_t pid;

	/* Initialize random number generator. */
	srand(time(NULL));

	/*
	 * Create pipe (fd[0] is the read end, fd[1] is the write end).
	 * File descriptors are inherited by child upon fork, and point
	 * to the same underlying objects.
	 */
	assert(pipe(fd) != -1);

	/* Fork and let the game begin. */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */
		/* Close read end. */
		assert(close(fd[0]) != -1);

		/* Open /dev/urandom. */
		int rndfd;

		rndfd = open("/dev/urandom", O_RDONLY);
		assert(rndfd != -1);

		int i;
		for (i = 0; i < MAX_BLOCKS; i++) {
			/* Calculate block size. */
			block.b_len = 1 + rand() % (MAX_DATALEN-1);

			/*
			 * Read random data.
			 * XXX: Should we trust read(2) to provide us with all
			 * the data we want, in one single call ?
			 */
			assert(read(rndfd, block.b_data, block.b_len) == block.b_len);

			/* Calculate the SHA hash and pack it in the struct .*/
			SHA1(block.b_data, block.b_len, block.b_sha);

			/* Write block to pipe. */
			assert(write(fd[1], &block, sizeof(block))
			    == sizeof(block));
		}

		assert(close(rndfd) != -1);

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		printf("passed\n");
	} else {
		/* We are inside the child. */
		ssize_t i, bytesread, rv;

		/* Close write end. */
		assert(close(fd[1]) != -1);

		for (i = 0; i < MAX_BLOCKS; i++) {
			/* Read block from pipe. */
			bytesread = 0;
			do {
				rv = read(fd[0], (char *)&block + bytesread,
				    sizeof(block) - bytesread);
				assert(rv != -1);
				bytesread += rv;
			} while(bytesread < sizeof(block));

			/* A little bit paranoid. */
			assert(bytesread == sizeof(block));

			/*
			 * Re-calculate the SHA hash and compare it with the old
			 * one.
			 */
			char newsha[41];

			SHA1(block.b_data, block.b_len, newsha);
			assert(memcmp(newsha, block.b_sha, SHA_DIGEST_LENGTH) == 0);
		}
	}

	return (EXIT_SUCCESS);
}
