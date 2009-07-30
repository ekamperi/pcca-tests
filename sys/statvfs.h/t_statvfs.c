/*
 * Copyright (c) 2009, Stathis Kamperis
 * All rights reserved.

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
#include <sys/statvfs.h>

int main(int argc, char *argv[])
{
	struct statvfs buf;
	int rv;

	/*
	 * The following members are mandated by POSIX.
	 * If there is one missing, we will fail at compile time.
	 */
	(void)buf.f_bsize;	/* File system block size. */
	(void)buf.f_frsize;	/* File system block size. */
	(void)buf.f_blocks;	/* Total number of blocks on file system. */
	(void)buf.f_bfree;	/* Total number of free blocks. */
	(void)buf.f_bavail;	/* Number of free blocks available to
				   non-privileged process. */
	(void)buf.f_files;	/* Total number of file serial numbers. */
	(void)buf.f_ffree;	/* Total number of free file serial numbers. */
	(void)buf.f_favail;	/* Number of file serial numbers available to
				   non-privileged process. */
	(void)buf.f_fsid;	/* File system ID. */
	(void)buf.f_flag;	/* Bit mask of f_flag values. */
	(void)buf.f_namemax;	/* Maximum filename length. */

	/* Obtain file system information. */
	rv = statvfs(argv[0], &buf);
	assert(rv == 0);

	/*
	 * POSIX says that statvfs-ability doesn't have anything to do with
	 * read, write or execute permissions of the named file.
	 */
	rv = statvfs("sandbox/file000", &buf);
	assert(rv == 0);

	/* Search permission is denied on a component of the path prefix. */
	rv = statvfs("sandbox/dir666/whatever", &buf);
	assert(rv == -1 && errno == EACCES);

	/* Loop exists in symbolic link resolution. */
	rv = statvfs("sandbox/infloop", &buf);
	assert(rv == -1 && errno == ELOOP);

	/* No such file or empty string. */
	rv = statvfs("", &buf);
	assert(rv == -1 && errno == ENOENT);

	rv = statvfs("sandbox/thisdefinitelydoesntexist", &buf);
	assert(rv == -1 && errno == ENOENT);

	/* Component of path is not a directory. */
	rv = statvfs("sandbox/notadir/whatever", &buf);
	assert(rv == -1 && errno == ENOTDIR);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
