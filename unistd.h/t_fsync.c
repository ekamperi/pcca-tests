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

#define _XOPEN_SOURCE 600

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define FILEPATH	"sandbox/fsync.t"

int
main(void)
{
	int fd;

	/* Create new file inside our sandbox. */
	fd = open(FILEPATH, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	assert(fd != -1);

	/* Write some data in the file */
	char data[] = "All I know is what the words know, and dead things, "
	    "and that makes a handsome little sum, with a beginning and a "
	    "middle and an end, as in the well-built phrase and the long "
	    "sonata of the dead."
	    "						 -- Samuel Beckett\n";
	assert(write(fd, data, sizeof(data)) == sizeof(data));

	/* Sync data to disk */
	assert(fsync(fd) != -1);

	/* Close file */
	assert(close(fd) != -1);

	/* Although we created the file inside the sandbox, still delete it */
	assert(unlink(FILEPATH) != -1);

	printf ("passed\n");

	return (EXIT_SUCCESS);
}
