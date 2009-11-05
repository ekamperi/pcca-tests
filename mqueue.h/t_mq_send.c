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
#include <string.h>	/* memset() */

#define	MQNAME	"/t_mq_send"

int main(void)
{
	struct mq_attr attr;
	mqd_t md;
       	int rv;

	/* Invalid message queue descriptor. */
	rv = mq_send(-1, "", 0, 0);
	assert (rv == -1 && errno == EBADF);

	/*
	 * Priority is out of range 0...{MQ_PRIO_MAX}-1
	 * Mind that count starts from 0.
	 */
	long maxprio = -1;
#ifdef _SC_MQ_PRIO_MAX
	maxprio = sysconf(_SC_MQ_PRIO_MAX);
#endif
	if (maxprio == -1) {
		/*
		 * Use some ridiculously high value.
		 * Linux claims that supports 32768 priorities!
		 */
		maxprio = 65536;
	}
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md != 1);

	rv = mq_send(md, "foo", sizeof("foo"), maxprio);
	assert(rv == -1 && errno == EINVAL);

	mq_close(md);
	mq_unlink(MQNAME);

	/*
	 * Message size is larger than maximum allowed message size.
	 * The latter is implementation defined. In NetBSD happens to
	 * be 16*1024 as defined in sys/mqueue.h and kern/sys_mqueue.c.
	 * We use a "sufficiently" large value to cover other
	 * implemenetations as well.
	 */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md != -1);

	char *p;
	rv = mq_send(md, p, 32768, /* priority */ 0);
	assert(rv == -1 && errno == EMSGSIZE);

	mq_close(md);
	mq_unlink(MQNAME);

	/* Same as previous but use a non-default maximum message size. */
	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 1;	/* Maximum number of messages. */
	attr.mq_msgsize = 50;	/* Maximum message size. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, &attr);
	assert(md != -1);

	p = malloc(2 * attr.mq_msgsize);
	assert(p != NULL);
	memset(p, 0xff, 2 * attr.mq_msgsize);	/* Make sure we don't terminate prematurely */

	rv = mq_send(md, p, 2 * attr.mq_msgsize, /* priority */ 0);
	assert(rv == -1 && errno == EMSGSIZE);

	free(p);

	mq_close(md);
	mq_unlink(MQNAME);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
