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
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main(void)
{
	struct termios t;
	int fd;

	/* Make sure we are associated with a tty. */
	assert(isatty(STDIN_FILENO) != 0);

	/* Get current termios structure. */
	assert(tcgetattr(STDIN_FILENO, &t) != -1);

	/* ... and set it again! */
	assert(tcsetattr(STDIN_FILENO, TCSANOW, &t) != -1);

	/* Bad file descriptor. */
	assert(tcsetattr(-1, TCSANOW, &t) == -1 && errno == EBADF);

	/* Invalid optional actions arguments. */
#if 0
	/*
	 * "In general, an implementation must be conservative in its sending
	 * behavior, and liberal in its receiving behavior... where the meaning
	 * is still clear. But here it isn't. Anyway, since most mainstream OSes
	 * don't validate input, disable it for now.
	 * Source: http://www.ietf.org/rfc/rfc0791.txt
	 */
	assert(tcsetattr(STDIN_FILENO, TCSANOW | TCSADRAIN, &t) == -1
	       && errno == EINVAL);

	assert(tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &t) == -1
	       && errno == EINVAL);

	assert(tcsetattr(STDIN_FILENO, TCSADRAIN | TCSAFLUSH, &t) == -1
	       && errno == EINVAL);
#endif
	assert(tcsetattr(STDIN_FILENO, -INT_MAX, &t) == -1
	       && errno == EINVAL);

	/* File descriptor is not associated with a terminal. */
	fd = open("sandbox/notatty", O_RDONLY);
	assert(fd != -1);
	assert(tcgetsid(fd) == (pid_t)-1 && errno == ENOTTY);
	assert(close(fd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
