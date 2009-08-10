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
#include <cpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct entry {
	int symbol;
	int value;
} table[] = {
	/*
	 * Undefined symbols will be caught by symgen.pl, so don't be
	 * too harsh here.
	 */
#ifdef	C_IRUSR
	{ C_IRUSR, 0000400 },
#endif
#ifdef	C_IWUSR
	{ C_IWUSR, 0000200 },
#endif
#ifdef	C_IXUSR
	{ C_IXUSR, 0000100 },
#endif
#ifdef	C_IRGRP
	{ C_IRGRP, 0000040 },
#endif
#ifdef	C_IWGRP
	{ C_IWGRP, 0000020 },
#endif
#ifdef	C_IXGRP
	{ C_IXGRP, 0000010 },
#endif
#ifdef	C_IROTH
	{ C_IROTH, 0000004 },
#endif
#ifdef	C_IWOTH
	{ C_IWOTH, 0000002 },
#endif
#ifdef	C_IXOTH
	{ C_IXOTH, 0000001 },
#endif
#ifdef	C_ISUID
	{ C_ISUID, 0004000 },
#endif
#ifdef	C_ISGID
	{ C_ISGID, 0002000 },
#endif
#ifdef	C_ISVTX
	{ C_ISVTX, 0001000 },
#endif
#ifdef	C_ISDIR
	{ C_ISDIR, 0040000 },
#endif
#ifdef	C_ISFIFO
	{ C_ISFIFO, 0010000 },
#endif
#ifdef	C_ISREG
	{ C_ISREG, 0100000 },
#endif
#ifdef	C_ISBLK
	{ C_ISBLK, 0060000 },
#endif
#ifdef	C_ISCHR
	{ C_ISCHR, 0020000 },
#endif
#ifdef	C_ISCTG
	{ C_ISCTG, 0110000 },
#endif
#ifdef	C_ISLNK
	{ C_ISLNK, 0120000 },
#endif
#ifdef	C_ISSOCK
	{ C_ISSOCK, 0140000 },
#endif
};


int main(void)
{
	size_t i, len;

	/* Get number of constants defined. */
	len = sizeof(table)/sizeof(table[0]);

	for (i = 0; i < len; i++)
		assert(table[i].symbol == table[i].value);

	/* This doesn't fit to the above table. */
#ifdef MAGIC
	assert(strcmp(MAGIC, "070707") == 0);
#endif

	printf("passed\n");

	return (EXIT_SUCCESS);
}
