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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `flock' structure describes a file lock and it must include the
	 * following members:
	 */
	struct flock f;

	(void)f.l_type;		/* Type of lock; F_RDLCK, F_WRLCK, F_UNLCK. */
#ifdef F_RDLCK
	f.l_type = F_RDLCK;
#endif
#ifdef F_WRLCK
	f.l_type = F_WRLCK;
#endif
#ifdef F_UNLCK
	f.l_type = F_UNLCK;
#endif

	(void)f.l_whence;	/* Flag for starting offset. */
#ifdef SEEK_SET
	f.l_whence = SEEK_SET;
#endif
#ifdef SEEK_CUR
	f.l_whence = SEEK_CUR;
#endif
#ifdef SEEK_END
	f.l_whence = SEEK_END;
#endif

	(void)f.l_start;	/* Relative offset in bytes. */
	(void)f.l_len;		/* Size; if 0 then until EOF. */
	(void)f.l_pid;		/* Process ID of the process holding the lock. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
