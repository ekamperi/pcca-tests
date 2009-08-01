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

#define _XOPEN_SOURCE 600	/* for d_ino */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `DIR' type must be defined, representing a directory stream.
	 * XXX: Why it is only possible to declare a pointer to DIR ?
	 * Otherwise an error of `unknown storage size' is generated.
	 */
	DIR *dirp;
	dirp = NULL;	/* To silence gcc warning. */

	/*
	 * The `dirent' structure must be defined, including the following
	 members:
	 */
	struct dirent dir;
	(void)dir.d_ino;	/* File serial number. */
	(void)dir.d_name[0];	/* Name of entry. */

	/*
	 * The `ino_t' type must be defined as an unsigned integer type.
	 * (See sys/types.h)
	*/
	ino_t i;
	i = 12345;	/* To silence gcc warning. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
