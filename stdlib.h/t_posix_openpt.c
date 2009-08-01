#define _XOPEN_SOURCE 600

#include <assert.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

#define MESSAGE	"Slave says hello!"

int main(void)
{
	int masterfd;
	int slavefd;
	char *pslavename;
	pid_t pid;

	/* Get a descriptor associated with a master pseudo terminal. */
	masterfd = posix_openpt(O_RDWR);
	assert(masterfd != -1);

	/* Grant access to the slave pseudo terminal. */
	assert(grantpt(masterfd) != -1);

	/* Unlock the pseudo terminal master/slave pair. */
	assert(unlockpt(masterfd) != -1);

	/* Get the device name of the slave. */
	pslavename = ptsname(masterfd);
	assert(pslavename != NULL);

	/* Open slave device. */
	slavefd = open(pslavename, O_RDWR);
	assert(slavefd != -1);

	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */

		/* This will perhaps block us. */
		char buf[100];
		ssize_t rv;

		rv = read(masterfd, buf, sizeof(buf));
		assert(rv != -1);

		assert(strncmp(buf, MESSAGE, sizeof(MESSAGE)) == 0);

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		/* Close file descriptors. */
		assert(close(slavefd) != -1);
		assert(close(masterfd) != -1);

		printf("passed\n");
	} else {
		/*
		 * Write to slave file descriptor. This, normally, will make
		 * the data appear in master.
		 */
		assert(write(slavefd, MESSAGE, sizeof(MESSAGE)) != -1);
	}

	return (EXIT_SUCCESS);
}
