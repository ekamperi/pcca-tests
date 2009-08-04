#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>

int main(void)
{

	/*
	 * The `sockaddr_un' structure must be defined, including
	 * at least the following members.
	 */
	struct sockaddr_un sun;

	(void)sun.sun_family;	/* Address family. */
	(void)sun.sun_path;	/* Socket pathname. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
