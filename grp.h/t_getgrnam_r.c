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

#define _XOPEN_SOURCE 600

#include <assert.h>
#include <grp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NTHREADS	50

/* Function prototypes. */
static void *threadfun(void *);

int main(void)
{
	pthread_t tid[NTHREADS];
	size_t i;

	/* Create the threads. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_create(&tid[i], NULL, threadfun, NULL) == 0);

	/* Wait for the treads to complete. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_join(tid[i], NULL) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
threadfun(void *arg)
{
	struct group grp;
	struct group *pgrp;
	long sz = -1;

#ifdef _SC_GETGR_R_SIZE_MAX
	sz = sysconf(_SC_GETGR_R_SIZE_MAX);

	/*
	 * Normally, we wouldn't allow for a fail/-1 here, in the sense that if
	 * an implementation defines a _SC_XXX symbol, it ought to return
	 * meaningful results when this symbol is passed as an argument to
	 * sysconf().
	 *
	 * But, since we have another test (unistd.h/t_unistd) checking for such
	 * inconsistencies, let's be a bit lenient.
	 */
	/* assert(sz != -1); */
#endif

	/*
	 * If we couldn't determine the size of the buffer via sysconf(),
	 * just use some 'large enough' value.
	 */
	char *buf;

	if (sz == -1)
		sz = 65536;

	buf = malloc(sz);
	assert(buf != NULL);

	/* Search for `root' group, many many times. */
	size_t i;

	for (i = 0; i < 100; i++) {
		assert(getgrnam_r("root", &grp, buf, sz, &pgrp) == 0);

		/* Make sure that getgrnam_r() does't lie to us. */
		assert(strcmp(pgrp->gr_name, "root") == 0);

		/* Since we are here, let's check `group's data structure members. */
		(void)pgrp->gr_name;
		(void)pgrp->gr_gid;
		while(*pgrp->gr_mem) {
			(void)*pgrp->gr_mem;
			pgrp->gr_mem++;
		}
	}

	/* We are done -- free resources. */
	free(buf);

	pthread_exit(NULL);
}
