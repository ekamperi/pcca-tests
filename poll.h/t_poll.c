#include <poll.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `pollfd' structure must be defined, including at least
	 * the following members.
	 */
	struct pollfd p;

	(void)p.fd;		/* The following descriptor being polled. */
	(void)p.events;		/* The input event flags (see below). */
	(void)p.revents;	/* The output event flags (see below). */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
