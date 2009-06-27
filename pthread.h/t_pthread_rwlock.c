#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	N         100
#define NREADERS   20

struct entry {
	int init;	/* Whether it has been initialized. */
	int code;
} table[N];

pthread_rwlock_t rwl;

/* Function prototypes. */
static void *rdthread(void *);
static void *wrthread(void *);

int main(void)
{
	pthread_t rd[NREADERS], wr;
	int i;

	/* */
	memset(table, 0, N * sizeof(struct entry));

	/* Create read-write lock with default parameters. */
	assert(pthread_rwlock_init(&rwl, NULL) == 0);

	/* Create writer thread. */
	assert(pthread_create(&wr, NULL, wrthread, (void *)NULL) == 0);

	/* Create readers threads. */
	for (i = 0; i < NREADERS; i++) {
		assert(pthread_create(&rd[i], NULL, rdthread, (void *)NULL)
		    == 0);
	}

	/* Wait for threads to complete. */
	assert(pthread_join(wr, NULL) == 0);
	for (i = 0; i < NREADERS; i++)
		assert(pthread_join(rd[i], NULL) == 0);

	/* Destroy read-write lock. */
	assert(pthread_rwlock_destroy(&rwl) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
rdthread(void *arg)
{
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < N; j++) {
			assert(pthread_rwlock_rdlock(&rwl) == 0);
			if (table[j].init == 1) {
				assert(table[j].code == j);
			}
			assert(pthread_rwlock_unlock(&rwl) == 0);
		}
	}

	pthread_exit(NULL);
}

static void *
wrthread(void *arg)
{
	int i, j;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < N; j++) {
			assert(pthread_rwlock_wrlock(&rwl) == 0);
			table[j].init = 1;
			table[j].code = j;
			assert(pthread_rwlock_unlock(&rwl) == 0);
		}
	}

	pthread_exit(NULL);
}
