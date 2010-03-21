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
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

/*
 * DragonFly implements shared memory objects as normal files, which is why
 * shm_open("/path/to/shared/object", ...); will fail if the user doesn't have
 * write permissions on the above path.
 *
 * Linux, open/Solaris and FreeBSD do otherwise. Specifically, open/Solaris
 * mandates that the path starts with a /. Conditionalize the whole thing,
 * to play nice with all parties.
 *
 * Also, make sure that the shared object's name doesn't collide with the
 * executable's name (in the DragonFly case).
 */
#ifdef	__DragonFly__
#define SHM_NAME	"t_mmap_shm_close2"
#else
#define SHM_NAME	"/t_mmap_shm_close2"
#endif
#define SHM_SIZE	16384

int	didsegfault = 0;

/* Function prototypes. */
static void myhandler(int sig);

int
main(void)
{
	/* Create a shared memory object that we will be mmap'ing. */
	int fd;

	fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	assert(fd != -1);

	/* Set the size of the shared memory object via ftruncate(). */
	assert(ftruncate(fd, SHM_SIZE) != -1);

	/* Ok, actually mmap() the memory region. */
	void *mmaddr;

	mmaddr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	assert(mmaddr != MAP_FAILED);

	/*
	 * The mmap() function adds an extra reference to the object associated
	 * with fd, which is not removed by a subsequent close() on that file
	 * descriptor. This reference is removed when there are no more mappings
	 * to the file.
	 */
	assert(shm_unlink(SHM_NAME) != -1);
	assert(close(fd) != -1);

	/* This shouldn't crash, as we haven't called munmap() yet. */
	*(char *)mmaddr = 1;

	/* Unmap the pages. */
	assert(munmap(mmaddr, SHM_SIZE) != -1);

	/*
	 * Install signal handler for SIGSEGV.
	 *
	 * We will be needing this, when we will try to access
	 * an unmapped page.
	 */
	assert(signal(SIGSEGV, myhandler) != SIG_ERR);

	/*
	 * This should cause a SIGSEGV signal being raised and 
	 * delivered to us.
	 */
	*(char *)mmaddr = 1;

	/* THIS SHOULD NEVER REACH HERE. */
	assert(0);
	return (EXIT_FAILURE);
}

static void
myhandler(int sig)
{
	/*
	 * We only expect SIGSEGV.
	 *
	 * We can't use printf(), exit() and the like inside a signal handler.
	 * Only async-signal safe functions shall be used. For a list, refer to:
	 *
	 * http://www.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html
	 */
	if (sig == SIGSEGV) {
		write(fileno(stdout), "passed\n", strlen("passed\n")+1);
		_exit(EXIT_SUCCESS);
	}

	/* If this is reached, the program will fail, which is what we want. */
}
