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
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	MQNAME	"/t_mq_ambig"

int main(void)
{
	char buf[100];
	mqd_t md;

	/*
	 * In the creation of a message queue, there is an ambiguity between
	 * `oflag' and `mode_t' with respect to which one of them takes
	 * precedence over the other.
	 *
	 * It seems that `oflag' is checked first and then `mode_t'.
	 */

	/*
	 * Create a READ only message queue, but with WRITE permission bits
	 * set, and then try to actually WRITE (i.e., mq_send() data to it).
	 */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDONLY, 0777, NULL);
	assert(md != (mqd_t)-1);

	assert(mq_send(md, buf, sizeof(buf), /* priority */ 0) == -1
	    && errno == EBADF);

	/* Close and remove the message queue. */
	assert(mq_close(md) != (mqd_t)-1);
	assert(mq_unlink(MQNAME) != (mqd_t)-1);

	/*
	 * Create a WRITE only message queue, but with READ permission bits
	 * set, and then try to actually READ (i.e., mq_receive() data from it).
	 */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0777, NULL);
	assert(md != (mqd_t)-1);

	assert(mq_receive(md, buf, sizeof(buf), /* priority */ 0) == -1
	    && errno == EBADF);

	/* Close and remove the message queue. */
	assert(mq_close(md) != (mqd_t)-1);
	assert(mq_unlink(MQNAME) != (mqd_t)-1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
