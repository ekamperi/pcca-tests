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
 * Original idea and code excerpts kindly provided by Giorgos Keramidas.
 */

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#define FORKLOG	"sandbox/fork.log"
#define	NFORKS	10

int
main(void)
{
	/* Open log file. */
	FILE *fp;
	fp = fopen(FORKLOG, "w");
	assert(fp != NULL);

	/* Set the stream to be non-buffered! */
	setbuf(fp, NULL);
	int fd;
	fd = fileno(fp);
	assert(fd >= 0);

	/* Get the file descriptor flags. */
	int fflag;
	fflag = fcntl(fd, F_GETFD);
	assert(fflag != -1);

	/*
	 * And set the close-on-exec bit.
	 * XXX: This seems to have no effect in buffers' flush, whatsoever.
	 * XXX: Is it exploitable in terms of test case writing ?
	 */
	assert(fcntl(fd, F_SETFD, fflag & FD_CLOEXEC) != -1);

	/* Huhu! */
	pid_t pid;
	size_t i;
	for (i = 0; i < NFORKS; i++) {
		pid = fork();
		assert(pid != (pid_t)-1);

		if (pid == 0) {
			/* We are inside the child. */
			break;
		} else {
			/* We are inside the parent. */
			int status;
			assert(wait(&status) == pid);
			fprintf(fp, "%s\n", "parent");
		}
	}

	if (pid != 0) {
		/* We are inside the parent. */
		assert(fclose(fp) != EOF);

		/* Reopen the file to count how many lines were printed. */
		fp = fopen(FORKLOG, "r");
		assert(fp != NULL);

		size_t cnt = 0;
		char buf[1024];
		while(!feof(fp)) {
			if (fgets(buf, sizeof(buf), fp) == NULL) {
				assert(feof(fp));
				break;
			}
			/* printf("%s", buf); */
			cnt++;
		}

		/* There should be one line per fork. */
		assert(cnt == NFORKS);
		assert(fclose(fp) != EOF);

		printf("passed\n");
	}

	return (EXIT_SUCCESS);
}
