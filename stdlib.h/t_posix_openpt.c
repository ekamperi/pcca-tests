/*
 * Copyright (c) 2009, Stathis Kamperis
 * All rights reserved.
 *
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
