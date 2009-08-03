#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>

int main(void)
{

	/* The ipc_perm structure must contain the following members. */
	struct ipc_perm ip;

	(void)ip.uid;	/* Owner's user ID. */
	(void)ip.gid;	/* Owner's group ID. */
	(void)ip.cuid;	/* Creator's user ID. */
	(void)ip.cgid;	/* Creator's group ID. */
	(void)ip.mode;	/* Read/write permission. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
