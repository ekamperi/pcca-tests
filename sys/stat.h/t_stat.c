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

#define _XOPEN_SOURCE   600	/* for st_rdev, st_blksize, st_blocks */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	struct stat st;

	(void)st.st_dev;	/* Device ID of device containing file. */
	(void)st.st_ino;	/* File serial number. */
	(void)st.st_mode;	/* Mode of file (see below). */
	(void)st.st_nlink;	/* Number of hard links to the file. */
	(void)st.st_uid;	/* User ID of file. */
	(void)st.st_gid;	/* Group ID of file. */
	(void)st.st_rdev;	/* Device ID (if file is character or block
				   special). */
	(void)st.st_size;	/* For regular files, the file size in bytes. */
	(void)st.st_atime;	/* Time of last access. */
	(void)st.st_mtime;	/* Time of last data modification. */
	(void)st.st_ctime;	/* Time of last status change. */
	(void)st.st_blksize;	/* A file system-specific preferred I/O block
				   size for this object. In some file system
				   types, this may vary from file to file. */
	(void)st.st_blocks;	/* Number of blocks allocated for this object.*/


	/*
	 * XXX: The bits defined by S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP,
	 * S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH, S_ISUID, S_ISGID, and S_ISVTX
	 * shall be unique.
	 */

	/*
	 * File mode bits.
	 * S_IRWXU is the bitwise-inclusive OR of S_IRUSR, S_IWUSR, and S_IXUSR.
	 */
#if defined(S_IRWXU) && defined(S_IRUSR) && defined(S_IWUSR) && defined(S_IXUSR)
	assert(S_IRWXU == (S_IRUSR | S_IWUSR | S_IXUSR));
#endif

	/*
	 * S_IRWXG is the bitwise-inclusive OR of S_IRGRP, S_IWGRP, and S_IXGRP.
	 */
#if defined(S_IRWXG) && defined(S_IRGRP) && defined(S_IWGRP) && defined(S_IXGRP)
	assert(S_IRWXG == (S_IRGRP | S_IWGRP | S_IXGRP));
#endif

	/*
	 * S_IRWXO is the bitwise-inclusive OR of S_IROTH, S_IWOTH, and S_IXOTH.
	 */
#if defined(S_IRWXO) && defined(S_IROTH) && defined(S_IWOTH) && defined(S_IXOTH)
	assert(S_IRWXO == (S_IROTH | S_IWOTH | S_IXOTH));
#endif

	/* Test for a directory. */
#ifdef S_ISDIR
	assert(stat("sandbox/dir777", &st) != -1);
	assert(S_ISDIR(st.st_mode) != 0);
#endif

	/* Test for a regular file. */
#ifdef S_ISREG
	assert(stat("sandbox/file777", &st) != -1);
	assert(S_ISREG(st.st_mode) != 0);
#endif

	/* Test for a symbolic link. */
#ifdef S_ISLN
	assert(stat("sandbox/fileloop", &st) != -1);
	assert(S_ISLNK(st.st_mode) != 0);
#endif

	/* Test for FIFO special file. */
#ifdef S_ISFIFO
	assert(stat("sandbox/fifo", &st) != -1);
	assert(S_ISFIFO(st.st_mode) != 0);
#endif

	/*
	 * XXX: Test for block special file, character special file and socket.
	 */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
