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
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define RO_SHM_NAME	"/t_mmap_errno_ro"
#define WO_SHM_NAME	"/t_mmap_errno_wo"

enum fdtype {
	FD_DONTCARE = -1,
	FD_RDONLY   = -2,
	FD_WDONLY   = -3,
	FD_INVALID  = -4
};

struct tentry {
	void *te_addr;
	size_t te_len;
	int te_prot;
	int te_flags;
	int te_fd;
	off_t te_off;
	int te_errno;
} ttable[] = {
	/*
	 * The fd argument is not for write and PROT_WRITE was specified for a
	 * MAP_SHARED type mapping.
	 */
	{ NULL,    1, PROT_WRITE, MAP_SHARED,  FD_RDONLY, 0, EACCES },
	{ NULL, 1024, PROT_WRITE, MAP_SHARED,  FD_RDONLY, 0, EACCES },

	/* The fd argument is not a valid open file descriptor. */
	{ NULL, 1, PROT_READ,  MAP_SHARED,  FD_INVALID, 0, EBADF },
	{ NULL, 1, PROT_READ,  MAP_PRIVATE, FD_INVALID, 0, EBADF },
	{ NULL, 1, PROT_READ,  MAP_FIXED,   FD_INVALID, 0, EBADF },

	{ NULL, 1024, PROT_WRITE, MAP_SHARED,  FD_INVALID, 0, EBADF },
	{ NULL, 1024, PROT_WRITE, MAP_PRIVATE, FD_INVALID, 0, EBADF },
	{ NULL, 1024, PROT_WRITE, MAP_FIXED,   FD_INVALID, 0, EBADF },

	/* The value of len is zero. */
	{ NULL, 0, PROT_READ, MAP_SHARED,   FD_DONTCARE, 0, EINVAL },
	{ NULL, 0, PROT_READ, MAP_PRIVATE,  FD_DONTCARE, 0, EINVAL },
	{ NULL, 0, PROT_READ, MAP_FIXED,    FD_DONTCARE, 0, EINVAL },

	{ NULL, 0, PROT_WRITE, MAP_SHARED,  FD_DONTCARE, 0, EINVAL },
	{ NULL, 0, PROT_WRITE, MAP_PRIVATE, FD_DONTCARE, 0, EINVAL },
	{ NULL, 0, PROT_WRITE, MAP_FIXED,   FD_DONTCARE, 0, EINVAL },

	{ NULL, 0, PROT_READ | PROT_WRITE, MAP_SHARED,  FD_DONTCARE, 0,
	  EINVAL },
	{ NULL, 0, PROT_READ | PROT_WRITE, MAP_PRIVATE, FD_DONTCARE, 0,
	  EINVAL },
	{ NULL, 0, PROT_READ | PROT_WRITE, MAP_FIXED,   FD_DONTCARE, 0,
	  EINVAL },

        /*
	 * The value of flags is invalid (Both MAP_SHARED and MAP_PRIVATE are
	 * set).
	 */
        { NULL, 1, PROT_READ,  MAP_SHARED | MAP_PRIVATE, FD_DONTCARE, 0,
	  EINVAL },
        { NULL, 1, PROT_WRITE, MAP_SHARED | MAP_PRIVATE, FD_DONTCARE, 0,
	  EINVAL },
        { NULL, 1, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_PRIVATE,
	  FD_DONTCARE, 0, EINVAL },

        { NULL, 1024, PROT_READ, MAP_SHARED  | MAP_PRIVATE, FD_DONTCARE, 0,
	  EINVAL },
	{ NULL, 1024, PROT_WRITE, MAP_SHARED | MAP_PRIVATE, FD_DONTCARE, 0,
	  EINVAL },
        { NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_PRIVATE,
	  FD_DONTCARE, 0, EINVAL },

	/*
	 * The value of flags is invalid (neither MAP_PRIVATE nor MAP_SHARED
	 * is set.
	 */
	{ NULL, 1, PROT_READ,  ~(MAP_PRIVATE | MAP_SHARED), FD_DONTCARE,
	  0, EINVAL },
	{ NULL, 1, PROT_WRITE, ~(MAP_PRIVATE | MAP_SHARED), FD_DONTCARE,
	  0, EINVAL },
	{ NULL, 1, PROT_READ | PROT_WRITE, ~(MAP_SHARED | MAP_PRIVATE),
	  FD_DONTCARE, 0, EINVAL },

	/*
	 * The fd is not open for read, regardless of the protection
	 * specified.
	 */
	{ NULL, 1, PROT_READ,  MAP_SHARED,  FD_WDONLY, 0, EACCES },
	{ NULL, 1, PROT_READ,  MAP_PRIVATE, FD_WDONLY, 0, EACCES },
	{ NULL, 1, PROT_WRITE, MAP_SHARED,  FD_WDONLY, 0, EACCES },
	{ NULL, 1, PROT_WRITE, MAP_PRIVATE, FD_WDONLY, 0, EACCES },

	/*
	 * The fd is not open for write and PROT_WRITE was specified for a
	 * MAP_SHARED type mapping.
	 */
	{ NULL, 1, PROT_WRITE, MAP_SHARED, FD_RDONLY, 0, EACCES }
};

int
main(void)
{
	/*
	 * Create shared memory objects that we will be mmap'ing
	 * One read-only and one write-only.
	 */
	int rofd, wofd;

	rofd = shm_open(RO_SHM_NAME, O_CREAT | O_EXCL | O_RDONLY,
	    S_IRUSR | S_IWUSR);
	assert(rofd != -1);

	wofd = shm_open(WO_SHM_NAME, O_CREAT | O_EXCL | O_WRONLY,
	    S_IRUSR | S_IWUSR);
	assert(wofd != -1);

	/* Run the tests */
	size_t i, N;

	N = sizeof(ttable) / sizeof(struct tentry);
	for (i = 0; i < N; i++) {
		struct tentry *te = &ttable[i];
		assert(te);

		/* Assign the file descriptor accordingly */
		switch(te->te_fd) {
		case FD_DONTCARE:
			te->te_fd = rofd;
			break;
		case FD_RDONLY:
			te->te_fd = rofd;
			break;
		case FD_WDONLY:
			te->te_fd = wofd;
			break;
		case FD_INVALID:
			te->te_fd = -1;
			break;
		default:
			assert(0);
			/* NEVER REACHED */
		}

		assert(mmap(te->te_addr, te->te_len, te->te_prot, te->te_flags,
			te->te_fd, te->te_off) == MAP_FAILED
		    && errno == te->te_errno);
	}

	/* Cleanup */
	assert(shm_unlink(RO_SHM_NAME) != -1);
	assert(shm_unlink(WO_SHM_NAME) != -1);
	assert(close(rofd) != -1);
	assert(close(wofd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
