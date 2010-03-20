/*
 * Copyright (c) 2010, Stathis Kamperis
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
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

/*
 * DragonFly implements shared memory objects as normal files, which is why
 * shm_open("/path/to/shared/object", ...); will fail if the user doesn't have
 * write permissions on the above path.
 *
 * Linux, open/Solaris and FreeBSD do otherwise. In any case, we omit the
 * leading / to play well with all parties.
 */
#define SHM_NAME	"t_mmap"
#define SHM_SIZE	10000

int
main(void)
{
	/* Create a shared memory object that we will be mmap'ing */
	int fd;

	fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	assert(fd != -1);

	/* Set the size of the shared memory object via ftruncate() */
	assert(ftruncate(fd, SHM_SIZE) != -1);

	/*
	 * Start mapping progressively more and more memory,
	 * until we exhaust our address space.
	 */
	size_t mmsize;
	void *mmaddr;
	int nomem = 0;

	for (mmsize = 0; mmsize < SIZE_MAX; mmsize += SHM_SIZE) {
		mmaddr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE,
		    MAP_SHARED, fd, 0);
		if (mmaddr == MAP_FAILED && errno == ENOMEM) {
			nomem = 1;
			break;
		}

		/* For no other reason than ENOMEM, shall we fail. */
		assert(mmaddr != MAP_FAILED);
	}

	/* Cleanup */
	/* XXX: Is there a way to unmap those pages that we mapped ? */
	assert(shm_unlink(SHM_NAME) != -1);
	assert(close(fd) != -1);

	/* All the fuzz was about this */
	assert(nomem == 1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
