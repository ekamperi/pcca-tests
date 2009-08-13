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
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*
 * Missing baud rates symbols will be caught by symgen.pl,
 * so be a bit lenient here.
 */
speed_t speeds[] = {
#ifdef B0
	B0,
#endif
#ifdef B50
	B50,
#endif
#ifdef B75
	B75,
#endif
#ifdef B110
	B110,
#endif
#ifdef B134
	B134,
#endif
#ifdef B150
	B150,
#endif
#ifdef B200
	B200,
#endif
#ifdef B300
	B300,
#endif
#ifdef B600
	B600,
#endif
#ifdef B1200
	B1200,
#endif
#ifdef B1800
	B1800,
#endif
#ifdef B2400
	B2400,
#endif
#ifdef B4800
	B4800,
#endif
#ifdef B9600
	B9600,
#endif
#ifdef B19200
	B19200,
#endif
#ifdef B38400
	B38400
#endif
};

int main(void)
{
	struct termios t;
	speed_t ns, s;
	size_t i, speedfound;

	/* Make sure we are associated with a tty. */
	assert(isatty(STDOUT_FILENO) != 0);

	/* Get current termios structure. */
	assert(tcgetattr(STDOUT_FILENO, &t) != -1);

	/*
	 * Extract input speed.
	 * XXX: Can conformant implementations provide a speed beyond B38400 ?
	 */
	s = cfgetispeed(&t);

	speedfound = 0;
	for (i = 0; i < sizeof(speeds) / sizeof(speeds[0]); i++) {
		if (s == speeds[i]) {
			speedfound = 1;
			break;
		}
	}

	assert(speedfound == 1);

	/*
	 * Set new input speed.
	 * But first make sure that we don't set the speed to the old value.
	 */
	ns = s;
	for (i = 0; i < sizeof(speeds) / sizeof(speeds[0]); i++) {
		if (speeds[i] != s) {
			ns = speeds[i];
			break;
		}
	}

	/*
	 * A bit paranoid, since this assertion would fail only if there was
	 * just one baud rate available.
	 */
	assert(ns != s);
	cfsetispeed(&t, ns);

	/* Make sure the new input speed was actually set. */
	s = cfgetispeed(&t);
	assert(s == ns);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
