#define _XOPEN_SOURCE 600

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>

int main(void)
{
	struct iovec iov;

	(void)iov.iov_base;	/* Base address of a memory region for
				   input or output. */
	(void)iov.iov_len;	/* The size of the memory pointed to
				   by iov_base. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
