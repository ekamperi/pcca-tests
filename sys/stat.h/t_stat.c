#define _XOPEN_SOURCE   600	/* for st_rdev, st_blksize, st_blocks */

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

	printf("passed\n");

	return (EXIT_SUCCESS);
}
