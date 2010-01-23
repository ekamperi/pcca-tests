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
#include <limits.h>	/* for LONG_MAX */
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */

#define	MQNAME	"/t_mq_open"

int
main(void)
{
	mqd_t md;

	/* ------------------------------------------------------------------ */
	/* Empty message queue name. */
	assert(mq_open("", O_CREAT | O_EXCL | O_RDWR, 0700, NULL) == (mqd_t)-1
	    && errno == EINVAL);


	/* ------------------------------------------------------------------ */
	/* O_CREAT is not set and the named mqueue doesn't exist. */
	assert(mq_open("/t_mq_definitelydoesntexist", O_RDWR, 0700, NULL)
	       == (mqd_t)-1 && errno == ENOENT);


	/* ------------------------------------------------------------------ */
	/* Pathname is too long. XXX Probe host OS to report real PATH_MAX. */
	char *pathname =  malloc(65536);
	assert(pathname != NULL);

	/* Make sure we don't terminate prematurely. */
	memset(pathname, 0xFF, 65536);

	assert(mq_open(pathname, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL)
	       == -1 && errno == ENAMETOOLONG);
	free(pathname);


	/* ------------------------------------------------------------------ */
	/* Message queue already exists and O_CREAT, O_EXCL are both set. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md != (mqd_t)-1);

	assert(mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL)
	       == (mqd_t)-1 && errno == EEXIST);

	assert(mq_close(md) != -1);
	assert(mq_unlink(MQNAME) != -1);


        /* ------------------------------------------------------------------ */
	/* Try to open a read only message queue for write. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL, 0400, NULL);
	assert(md != (mqd_t)-1);

	assert(mq_open(MQNAME, O_RDWR)   == (mqd_t)-1 && errno == EACCES);
	assert(mq_open(MQNAME, O_WRONLY) == (mqd_t)-1 && errno == EACCES);

	assert(mq_close(md) != -1);
	assert(mq_unlink(MQNAME) != -1);


	/* ------------------------------------------------------------------ */
	/* Try to open a write only message queue for read. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL, 0200, NULL);
	assert(md != (mqd_t)-1);

	assert(mq_open(MQNAME, O_RDWR)   == (mqd_t)-1 && errno == EACCES);
	assert(mq_open(MQNAME, O_RDONLY) == (mqd_t)-1 && errno == EACCES);

	assert(mq_close(md) != -1);
	assert(mq_unlink(MQNAME) != -1);


	/* ------------------------------------------------------------------ */
	/* Try to open a queue with enormous capacity. */
	struct mq_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = LONG_MAX;
	attr.mq_msgsize = 1024;

	assert(mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, &attr) == -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
