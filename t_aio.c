#include <aio.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char mybuf[1000];
	struct aiocb iocb;
	int fd;

	/* Open file to read from. */
	fd = open(argv[0], O_RDONLY);
	assert(fd >= 0);

	/* Populate aiocb data structure. */
	memset(&iocb, 0, sizeof(iocb));
	iocb.aio_nbytes = sizeof(mybuf);
	iocb.aio_fildes = fd;
	iocb.aio_offset = 0;
	iocb.aio_buf = mybuf;

	/* Issue an asynchronous read request. */
	assert(aio_read(&iocb) != -1);

	/* Wait for request to complete. */
	while(aio_error(&iocb) == EINPROGRESS)
		/* VOID */ ;

	/* Get the final status of request. */
	assert(aio_return(&iocb) != -1);

	/* Close file. */
	close(fd);

	return (EXIT_SUCCESS);
}
