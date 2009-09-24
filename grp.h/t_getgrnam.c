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
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	struct group *pgrp;

	/* Try to search for an inexistent group. */
	pgrp = getgrnam("Cosmos is all that is or ever was or ever will be."	\
	    "Our feeblest contemplations of the Cosmos stir us — there is a"	\
	    "tingling in the spine, a catch in the voice, a faint sensation,"	\
	    "as if a distant memory, of falling from a height. We know we are"	\
	    "approaching the greatest of mysteries."				\
	    "Carl Sagan, The Cosmos.");
	assert(pgrp == NULL);

	/*
	 * Try to search for root group.
	 *
	 * POSIX doesnt, to my knowledge, explicitly require the existence of
	 * the root user (or group), but it refers to the former occasionally.
	 * E.g.,
	 * http://www.opengroup.org/onlinepubs/009695399/functions/getpwuid.html
	 */
	pgrp = getgrnam("root");
	assert(pgrp != NULL);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
