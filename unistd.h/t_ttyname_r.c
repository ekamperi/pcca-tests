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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syslimits.h>

/*
 * ttyname_r(3) provides a different prototype than IEEE Std 1003.1-2001.
 * Check only errno variale values.
 */

int main(int argc, char *argv[])
{
	char big[PATH_MAX];
	char tiny[] = "/dev/ ";
	int fd;

	/* valid tty -- big buffer */
	fd = open("/dev/ttyp0", O_RDONLY);
	assert(fd >= 0);
	assert(ttyname_r(fd, big, sizeof(big)-1) != NULL);
	close(fd);

	/* valid tty -- tiny buffer */
	fd = open("/dev/ttyp0", O_RDONLY);
	assert(fd >= 0);
	assert(ttyname_r(fd, tiny, sizeof(tiny)-1) == NULL && errno == ERANGE);
	close(fd);

	/* bad file descriptor */
	fd = -1;
	assert(ttyname_r(fd, big, sizeof(big)-1) == NULL && errno == EBADF);

	/* invalid tty */
	fd = open(argv[0], O_RDONLY);
	assert(fd >= 0);
	assert(ttyname_r(fd, big, sizeof(big)-1) == NULL && errno == ENOTTY);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
