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
#include <string.h>	/* for memset() */

#define	MQNAME	"/t_mq_setattr"

int main(void)
{
	/* Invalid (or so we hope) message queue descriptor. */
	struct mq_attr attr, curattr;

	assert(mq_setattr((mqd_t)-1, &attr, NULL    ) == -1 && errno == EBADF);
	assert(mq_setattr((mqd_t)-1, &attr, &curattr) == -1 && errno == EBADF);

	/*
	 * mq_getattr() must report the same exact values as those we provided
	 * to mq_open() upon the queue creation.
	 */
	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 10;		/* Maximum number of messages. */
	attr.mq_msgsize = 1024;		/* Maximum message size. */

	mqd_t md;
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDWR, 0700, &attr);
	assert(md != (mqd_t)-1);

	assert(mq_getattr(md, &curattr) != -1);
	assert(curattr.mq_maxmsg  == 10);
	assert(curattr.mq_msgsize == 1024);
	assert(curattr.mq_curmsgs == 0);

	/*
	 * Use mq_setattr() to set attributes.
	 * POSIX says that the values of the mq_maxmsg, mq_msgsize, and
	 * mq_curmsgs members of the mq_attr structure shall be ignored by
	 * mq_setattr().
	 */
	struct mq_attr newattr, oldattr;

	newattr.mq_maxmsg = 101;
	newattr.mq_msgsize = 3000;
	newattr.mq_curmsgs = 2;
	assert(mq_setattr(md, &newattr, &oldattr) != -1);

	assert(oldattr.mq_maxmsg  == 10);
	assert(oldattr.mq_msgsize == 1024);
	assert(oldattr.mq_curmsgs == 0);

	assert(curattr.mq_maxmsg  == 10);
	assert(curattr.mq_msgsize == 1024);
	assert(curattr.mq_curmsgs == 0);

	/* Disassociate message queue from system. */
	assert(mq_close(md) != -1);

	/* Remove message queue from system. */
	assert(mq_unlink(MQNAME) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
