#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>	/* for memset() */
#include <sys/mman.h>
#include <sys/stat.h>

#define SHMNAME		"/t_shm"
#define SHMSIZE		10000

struct sharedregion {
	size_t size;
	char buf[SHMSIZE];
};

int
main(void)
{
	/* Create a new shared memory object. */
	int shmd;

	shmd = shm_open(SHMNAME, O_CREAT | O_RDWR, 0777);
	assert(shmd != -1);

	/* Set shared memory object's size. */
	assert(ftruncate(shmd, sizeof(struct sharedregion)) != -1);

	/* Map the memory object. */
	struct sharedregion *ptr;

	ptr = mmap(NULL, sizeof(struct sharedregion), PROT_READ | PROT_WRITE,
		   MAP_SHARED, shmd, 0);
	assert(ptr != MAP_FAILED);

	/* Write something to the shared region, although noone will read it. */
	ptr->size = SHMSIZE;
	memset(ptr->buf, 0, SHMSIZE);

	/* Disassociate from the shared memory object. */
	assert(close(shmd) != -1);

	/* Remove the shared memory object from the system. */
	assert(shm_unlink(SHMNAME) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
