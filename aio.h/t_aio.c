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

#include <aio.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	char mybuf[1000];
	struct aiocb iocb;
	int fd;

	/* Open file to read from. */
	fd = open(argv[0], O_RDONLY);
	assert(fd != -1);

	/* Populate aiocb data structure. */
	memset(&iocb, 0, sizeof(iocb));
        iocb.aio_fildes = fd;
        iocb.aio_offset = 0;
        iocb.aio_buf = mybuf;
	iocb.aio_nbytes = sizeof(mybuf);
	iocb.aio_sigevent.sigev_notify = SIGEV_NONE;

	/* Issue an asynchronous read request. */
	assert(aio_read(&iocb) != -1);

	/* Wait for request to complete. */
	while(aio_error(&iocb) == EINPROGRESS)
		/* VOID */ ;

	/* Get the final status of request. */
	assert(aio_return(&iocb) != -1);

	/* Close file. */
	assert(close(fd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
