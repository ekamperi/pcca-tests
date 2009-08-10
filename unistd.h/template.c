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
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int supported1 = 0;	/* Via sysconf(3). */
	int supported2 = 0;	/* Via symbol constant definition. */
	long rv;

#ifdef _SC_MYSYMBOL
	errno = 0;
	rv = sysconf(_SC_MYSYMBOL);

	/* If _SC_MYSYMBOL is defined, then sysconf(3) should recognise it. */
	assert(rv != -1 || errno == 0);

	/*
	 * For these particular variables of <unistd.h>, sysconf(3) is allowed
	 * to either return -1 or 200112L.
	 */
	assert(rv == -1 || rv == 200112L);

	supported1 = (rv == -1) ? -1 : 1;
#endif

#ifdef _POSIX_MYSYMBOL
	/*
	 * If a symbolic constant in <unistd.h> is defined with a value greater
	 * than zero, all headers, data types and functions shall be present
	 * _AND_ shall operate as specified.
	 * If it's -1 it is definitely not supported (nor headers, data types,
	 * functions, nor any underlying implementation).
	 * If it's  0 it's inconclusive. The implementation is expected to
	 * provide headers, data types and functions but the user must query
	 * sysconf(3) to see if there is any _underlying_ implementation.
	 */
	#if (_POSIX_MYSYMBOL - 0L) > 0L
		supported2 = 1;
	#elif (_POSIX_MYSYMBOL - 0L) == -1L
		supported2 = -1;
	#endif
#endif

	/* Make sure we don't get contradictory results. */
	assert(supported1 * supported2 != -1);

	/* Make sure that at least one of the query methods works. */
	assert(supported1 != 0 || supported2 != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
