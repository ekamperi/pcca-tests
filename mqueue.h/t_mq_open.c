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

#define	MQNAME	"/t_mq_open"
#define	PATH_MAX 1024	/* XXX */

int main(void)
{
	mqd_t md, md2;

	/* Empty message queue name. */
	assert(mq_open("", O_CREAT | O_EXCL | O_RDWR, 0777, NULL) == (mqd_t)-1
	    && errno == EINVAL);

	/* O_CREAT is not set and the named mqueue doesn't exist. */
	md = mq_open("nonexistentmqueuename", O_WRONLY, 0700, NULL);
	assert (md == (mqd_t)-1 && errno == ENOENT);

	/* Pathname is too long. */
	char *pathname = malloc(2 * PATH_MAX);
	assert(pathname != NULL);
	memset(pathname, 0xff, 2 * PATH_MAX);	/* Make sure we don't terminate
						   prematurely. */

	md = mq_open(pathname, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md == (mqd_t)-1 && errno == ENAMETOOLONG);
	free(pathname);

	/* Name already exists and O_CREAT, O_EXCL are both set. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md != (mqd_t)-1);

	assert(mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL)
	       == (mqd_t)-1 && errno == EEXIST);
	mq_close(md);
	mq_unlink(MQNAME);

	/* Try to open a read only message queue for write. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL, 0400, NULL);
	assert(md != (mqd_t)-1);

	md2 = mq_open(MQNAME, O_RDWR);
	assert(md2 == (mqd_t)-1 && errno == EACCES);

	md2 = mq_open(MQNAME, O_WRONLY);
	assert(md2 == (mqd_t)-1 && errno == EACCES);

	mq_close(md);
	mq_unlink(MQNAME);

	/* Try to open a write only message queue for read. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL, 0200, NULL);
	assert(md != (mqd_t)-1);

	md2 = mq_open(MQNAME, O_RDWR);
	assert(md2 == (mqd_t)-1 && errno == EACCES);

	md2 = mq_open(MQNAME, O_RDONLY);
	assert(md2 == (mqd_t)-1 && errno == EACCES);

	mq_close(md);
	mq_unlink(MQNAME);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
