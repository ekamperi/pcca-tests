/*
 * Copyright (c) 2010, Stathis Kamperis
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
#include <limits.h>	/* for LONG_MAX */
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */

#define	MQNAME	"/t_mq_send_dos"

int
main(void)
{
	/*
	 * Create a message queue with enormous capacity.
	 * According to POSIX, mq_maxmsg field is of `long' data type.
	 */
	struct mq_attr attr;
	mqd_t md;

	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = LONG_MAX;	/* Maximum number of messages. */
	attr.mq_msgsize = 1024;		/* Maximum message size. */

	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, &attr);
	if (md == (mqd_t)-1) {
		assert(errno == EINVAL);
		printf("passed\n");
		return (EXIT_SUCCESS);
	}

	/*
	 * Start sending messages until we consume all memory.
	 *
	 * In OSes that implement message queues inside the kernel,
	 * this could lead to a panic and a denial of service attack.
	 *
	 * Such implementations may be found in {Net, DragonFly}BSD, as
	 * opposed to the userland mqueue incarnation of Solaris.
	 */
	char buf[1024];
	long i;

	for (i = 0; i < LONG_MAX; i++)
		assert(mq_send(md, buf, sizeof(buf), /* priority */ 0) != -1);

	assert(mq_close(md) != -1);
	assert(mq_unlink(MQNAME) != -1);

	printf("passed (Oh My God!)\n");

	return (EXIT_SUCCESS);
}
