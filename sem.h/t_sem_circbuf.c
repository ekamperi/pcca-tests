#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	TOTALSIZE	(1 << 15)
#define	BUFSIZE		(1 << 10)

#define	MAGICBYTE_A	(0xAB)
#define MAGICBYTE_B	(0xCD)

unsigned char buf[BUFSIZE];

sem_t sem_freebytes_buf1;
sem_t sem_freebytes_buf2;
sem_t sem_writtenbytes_buf1;
sem_t sem_writtenbytes_buf2;

/* Function prototypes. */
void *writer1(void *arg);
void *writer2(void *arg);
void *reader(void *arg);

int main(void)
{
	pthread_t wr1, wr2, rd;

	/* Initialize semaphores. */
	assert(sem_init(&sem_freebytes_buf1,
		   0 /* not shared between processes */,
		   BUFSIZE/2 /* semaphore value */) == 0);

	assert(sem_init(&sem_freebytes_buf2,
		   0 /* not shared between processes */,
		   BUFSIZE/2 /* semaphore value */) == 0);

        assert(sem_init(&sem_writtenbytes_buf1,
                   0 /* not shared between processes */,
                   0 /* semaphore value */) == 0);

        assert(sem_init(&sem_writtenbytes_buf2,
                   0 /* not shared between processes */,
                   0 /* semaphore value */) == 0);

	/* Create threads. */
	assert(pthread_create(&wr1, NULL, writer1, (void *)NULL) == 0);
	assert(pthread_create(&wr2, NULL, writer2, (void *)NULL) == 0);
	assert(pthread_create(&rd, NULL, reader, (void *)NULL) == 0);

	/* Wait until threads complete. */
	assert(pthread_join(wr1, NULL) == 0);
	assert(pthread_join(wr2, NULL) == 0);
	assert(pthread_join(rd, NULL) == 0);

	/* Cleanup. */
	assert(sem_destroy(&sem_freebytes_buf1) == 0);
	assert(sem_destroy(&sem_freebytes_buf2) == 0);
        assert(sem_destroy(&sem_writtenbytes_buf1) == 0);
        assert(sem_destroy(&sem_writtenbytes_buf2) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

void *writer1(void *arg)
{
	size_t i, pos;

	for (i = 0; i < TOTALSIZE; i++) {
		/* Calculate position in buffer. */
		pos = i % (BUFSIZE/2);

		assert(sem_wait(&sem_freebytes_buf1) == 0);
		buf[pos] = MAGICBYTE_A;
		/*printf("writer1: pos: %d byte: %d\n", pos, buf[pos]);*/
		assert(sem_post(&sem_writtenbytes_buf1) == 0);
	}

	pthread_exit(NULL);
}

void *writer2(void *arg)
{
	size_t i, pos;

	for (i = 0; i < TOTALSIZE; i++) {
		/* Calculate position in buffer. */
		pos = BUFSIZE/2 + (i % (BUFSIZE/2));

                assert(sem_wait(&sem_freebytes_buf2) == 0);
                buf[pos] = MAGICBYTE_B;
		/*printf("writer2: pos: %d byte: %d\n", pos, buf[pos]);*/
                assert(sem_post(&sem_writtenbytes_buf2) == 0);
	}

	pthread_exit(NULL);
}

void *reader(void *arg)
{
	size_t i, pos;

	for (i = 0; i < 2*TOTALSIZE; i++) {
		/* Calculate position in buffer. */
		pos = i % BUFSIZE;

		/* Are we in the first half part? */
		if (pos < BUFSIZE/2) {
			assert(sem_wait(&sem_writtenbytes_buf1) == 0);
			assert(buf[pos] == MAGICBYTE_A);
			/*printf("reader:  pos: %d byte: %d\n", pos, buf[pos]);*/
			sem_post(&sem_freebytes_buf1);
		}
		/* ... or the second half ? */
		else {
			sem_wait(&sem_writtenbytes_buf2);
			assert(buf[pos] == MAGICBYTE_B);
			/*printf("reader:  pos: %d byte: %d\n", pos, buf[pos]);*/
			sem_post(&sem_freebytes_buf2);
		}
	}

	pthread_exit(NULL);
}
