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
	rv = statvfs("sandbox/zeroperm", &buf);
	assert(rv == 0);

	/* Search permission is denied on a component of the path prefix. */
	rv = statvfs("sandbox/zeropermdir/whatever", &buf);
	assert(rv == -1 && errno == EACCES);

	/* Loop exists in symbolic link resolution. */
	rv = statvfs("sandbox/loop", &buf);
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
