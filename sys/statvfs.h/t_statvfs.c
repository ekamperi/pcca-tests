#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>

int main(int argc, char *argv[])
{
	struct statvfs buf;
	int rv;

	rv = statvfs(argv[0], &buf);
	assert(rv == 0);

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

	printf("passed\n");

	return (EXIT_SUCCESS);
}
