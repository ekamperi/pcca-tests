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
#include <limits.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <time.h>
#include <sys/wait.h>

#define	MQNAME	"/t_mq_timedsend24"

struct {
	time_t tv_sec;
	long tv_nsec;
} tstable[] = {
	{ 0, -1		},
	{ 0, -LONG_MAX	},
	{ 0, 1000000000	},
	{ 0, 1000000001	},
	{ 0, +LONG_MAX	}

        { 1, -1         },
        { 1, -LONG_MAX  },
        { 1, 1000000000 },
        { 1, 1000000001 },
        { 1, +LONG_MAX  }
};

int
main(void)
{
	/* Create a message queue with capacity `1'. */
	struct mq_attr attr;
	mqd_t md;

	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 1;	/* Maximum number of messages. */
	attr.mq_msgsize = 1024;	/* Maximum message size. */

	/*
	 * We intentionally omit the O_NONBLOCK flag, as we _want_ the queue to
	 * operate on blocking mode.
	 */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, &attr);
	assert(md != (mqd_t)-1);

	/* Send a message to fill in the queue. */
	assert(mq_send(md, "foo", sizeof("foo"), /* priority */ 0) != -1);

	/*
	 * Since we are on blocking mode, any invalid `nsec' field in the
	 * timeout structure we provide to mq_timedsend(), shall result in an
	 * EINVAL error.
	 */
	struct timespec now, timeout;
	size_t i;

	for (i = 0; i < sizeof(tstable) / sizeof(tstable[0]); i++) {
		timeout.tv_sec  = tstable[i].tv_sec;
		timeout.tv_nsec = tstable[i].tv_nsec;

		assert(mq_timedsend(md, "foo", sizeof("foo"), /* priority */ 0,
			&timeout) == -1 && errno == EINVAL);
	}

	/* Disassociate from message queue. */
	assert(mq_close(md) != -1);

	/* Remove message queue from the system. */
	assert(mq_unlink(MQNAME) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
