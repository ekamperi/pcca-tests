#define _XOPEN_SOURCE 600

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int masterfd;
	int slavefd;
	char *pslavename;

	/* Get a descriptor associated with a master pseudo terminal. */
	masterfd = posix_openpt(O_RDWR | O_NOCTTY);
	assert(masterfd != -1);

	/* Grant access to the slave pseudo terminal. */
	assert(grantpt(masterfd) != -1);

	/* Unlock the pseudo terminal master/slave pair. */
	assert(unlockpt (masterfd) != -1);
		  
	/* Get the device name of the slave. */
	pslavename = ptsname(masterfd);
	assert(pslavename != NULL);

	/* Open slave device. */
	slavefd = open(pslavename, O_RDWR|O_NOCTTY);
	assert(slavefd != -1);

	/* We are done -- close master and slave. */
	assert(close(slavefd) != -1);
	assert(close(masterfd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
