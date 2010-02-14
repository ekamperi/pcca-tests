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

#include <aio.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NAIO	100000

int
main(int argc, char *argv[])
{
	char mybuf[1000];
	struct aiocb iocb[NAIO];
	int fd;
	size_t i;

	/* Open file to read from. */
	fd = open(argv[0], O_RDONLY);
	assert(fd != -1);

	/* Populate the aiocb structures. */
	memset(iocb, 0, sizeof(iocb));
	for (i = 0; i < NAIO; i++) {
		iocb[i].aio_fildes = fd;
		iocb[i].aio_offset = 0;
		iocb[i].aio_buf = mybuf;
		iocb[i].aio_nbytes = sizeof(mybuf);
		iocb[i].aio_sigevent.sigev_notify = SIGEV_NONE;
		iocb[i].aio_lio_opcode = LIO_READ;
	}

	/*
	 * Issue all the read operations at the same time.
	 * And suspend until _all of them_ are served.
	 */
	struct aiocb *iocblist[NAIO];

	for (i = 0; i < NAIO; i++)
		iocblist[i] = &iocb[i];

	lio_listio(LIO_WAIT, iocblist, NAIO, NULL);

	/* At this point, no aio operation shall return busy. */
	for (i = 0; i < NAIO; i++)
		 assert(aio_error(&iocb[i]) != EINPROGRESS);

	/* Get the final status of requests. */
	for (i = 0; i < NAIO; i++)
		assert(aio_return(&iocb[i]) != -1);

	/* Close file. */
	assert(close(fd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
