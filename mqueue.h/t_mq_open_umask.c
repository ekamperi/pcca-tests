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
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MQNAME	"/t_mq_open_umask"

int
main(void)
{
	/*
	 * Set the file creation mask to u=rwx g=rwx o=rwx.
	 *
	 * We will check later on, if it is honoured during the creation
	 * of a new message queue.
	 */
	umask(0777);
	assert(umask(0777) == 0777);	/* Paranoia */

	/*
	 * Create the message queue with permission bits set to 777.
	 *
	 * But since the file creation mask is already 777, the queue should be
	 * created with 000.
	 */
	mqd_t md;

	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDWR, 0777, NULL);
	assert(md != (mqd_t)-1);

	/* Disassociate from the message queue. */
	assert(mq_close(md) != -1);

	/* Fork! */
	pid_t pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */

		/*
		 * The file creation mask isn't inherited by the child process
		 * during fork(), but we will set it to 000 anyway as we don't
		 * want it to interfere with our modes.
		 */
		umask(0);
		assert(umask(0) == 0);	/* Paranoia */

		mode_t modes[] = { 000,	001, 002, 004,	/* XXX: What about 000 ? */
				   010, 012, 011, 014,
				   020, 021, 022, 024,
				   040, 041, 042, 044,

				   100, 101, 102, 104,
				   110, 111, 112, 114,
				   120, 121, 122, 124,
				   140, 141, 142, 144,

				   200, 201, 202, 204,
				   210, 211, 212, 214,
				   220, 221, 222, 224,
				   240, 241, 242, 244,

				   400, 401, 402, 404,
				   410, 411, 412, 414,
				   420, 421, 422, 424,
				   440, 441, 442, 444

				   /*
				    * We expect or rather hope that the combined
				    * permission bits, e.g. 777, are covered by
				    * the above fundamental set.
				    */
		};

		size_t i;
		for (i = 0; i < sizeof(modes) / sizeof(*modes); i++)
		  assert(mq_open(MQNAME, O_CREAT, modes[i], NULL) == (mqd_t)-1
			    && errno == EACCES);

		/* Remove the message queue from the system. */
		assert(mq_unlink(MQNAME) != -1);
	} else {
		/* We are inside the parent. */

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		/*
		 * Determine if the child exited normally, or due to a SIGABRT
		 * signal being delivered to it by a failed assertion.
		 */
		if (WIFSIGNALED(status)) {
			assert(WTERMSIG(status) == SIGABRT);
			return (EXIT_FAILURE);
		} else {
			printf("passed\n");

			return (EXIT_SUCCESS);
		}
	}

	/* Only reached by child upon success. */
	return (EXIT_SUCCESS);
}
