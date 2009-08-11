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
#include <string.h>	/* memset() */
#include <sys/resource.h>

int main(void)
{
	struct rlimit rlm;

	/* Invalid resource parameter specified. */
	assert(setrlimit(-112233, &rlm) == -1 && errno == EINVAL);
	assert(setrlimit( 112233, &rlm) == -1 && errno == EINVAL);

#if 0
	/*
	 * Try setting a soft limit larger than hard limit.
	 * It seems that if DragonFly encounters a soft limit larger than hard
	 * limit, it enforces the former to be as large as the latter. Rather
	 * than returning EINVAL as POSIX mandates. On top of that it fails
	 * later with EPERM because we aren't privileged enough to increase our
	 * limits.
	 * See kern/kern_plimit.c:355.
	 */
	/* Zero out structure. */
	memset(&rlm, 0, sizeof(struct rlimit));

	/* Get current stack size limit. */
	assert(getrlimit(RLIMIT_STACK, &rlm) == 0);

	/* Make sure we don't overflow. */
	if (rlm.rlim_max + 1 > rlm.rlim_max) {
		rlm.rlim_cur = rlm.rlim_max + 1;

		fprintf(stderr, "soft: %lld\thard: %lld\n",
		    rlm.rlim_cur, rlm.rlim_max);

		if (setrlimit(RLIMIT_STACK, &rlm) == -1) {
			perror("setrlimit");
			fprintf(stderr, "It should fail with EINVAL\n");
		}

		struct rlimit newrlm;
		assert(getrlimit(RLIMIT_STACK, &newrlm) == 0);
		fprintf(stderr, "soft: %lld\thard: %lld\n",
		    newrlm.rlim_cur, newrlm.rlim_max);
	} else {
		fprintf(stderr, "(skipping check)\t");
	}
#endif

	/* Try increasing maximum limit value without being super-user. */
	/* Zero out structure. */
	memset(&rlm, 0, sizeof(struct rlimit));

	/* Get current stack size limit. */
	assert(getrlimit(RLIMIT_STACK, &rlm) == 0);

	/* Make sure we don't overflow. */
	if (rlm.rlim_max + 1 > rlm.rlim_max++)
		assert(setrlimit(RLIMIT_STACK, &rlm) == -1 && errno == EPERM);
	else
		fprintf(stderr, "(skipping check)\t");

	/*
	 * Supply invalid address for the rlimit structure.
	 * This is DragonFly specific.
	 */
#ifdef __DragonFly__
	assert(setrlimit(RLIMIT_STACK, 0) == -1 && errno == EFAULT);
#endif

	printf("passed\n");

	return (EXIT_SUCCESS);
}
