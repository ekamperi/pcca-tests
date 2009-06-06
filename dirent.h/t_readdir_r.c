/* Solaris needs this for bringing in the standard readdir_r() prototype. */
#ifdef __sun__
#define	_POSIX_PTHREAD_SEMANTICS
#endif

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	NTHREADS	5

pthread_mutex_t mtx_found;
int found = 0;

/* Function protorypes. */
void *myscandir(void *arg);

int main(int argc, char *argv[])
{
	pthread_t thpool[NTHREADS];
	DIR *dirp;
	int i;

	/* Initialize mutex. */
	assert(pthread_mutex_init(&mtx_found, NULL) == 0);

	/* Open directory stream. */
	dirp = opendir(".");
	assert(dirp != NULL);

	for (i = 0; i < NTHREADS; i++)
		assert(pthread_create(&thpool[i], NULL, myscandir,
			(void *)dirp) == 0);

	/* Wait for threads to complete. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_join(thpool[i], NULL) == 0);

	/* Cleanup. */
	assert(closedir(dirp) == 0);
	assert(pthread_mutex_destroy(&mtx_found) == 0);

	/* Make sure we found . and .. */
	assert(found == 2);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

void *myscandir(void *arg)
{
	DIR *dirp;
	struct dirent *dp;
	struct dirent *res;
	size_t sz = -1;

	dirp = (DIR *)arg;

	#ifdef NAME_MAX
		sz = (NAME_MAX > 255) ? NAME_MAX : 255;
	#else
		/*
		 * XXX: This is dangerous, as it is vulnerable to races. Issue 7
		 * introduces dirfd() that returns a descriptor associated with
		 * a directory stream. Then pathconf() is replaced by
		 * fpathconf(dirfd(dir), _PC_NAME_MAX), which eliminates the
		 * race condition.
		 */
		#ifdef	_PC_NAME_MAX
			sz = pathconf(argv[1], _PC_NAME_MAX));
			assert(sz != -1);
		#else
			/* We are unable to determine buffer size. Abort. */
			assert(sz != -1);
		#endif
	#endif

	dp = malloc(offsetof(struct dirent, d_name) + sz + 1);
	assert(dp != NULL);

	for (;;) {
		assert(readdir_r(dirp, dp, &res) == 0);

		/* Check if we have reached the end of the stream. */
		if (res == NULL)
			break;

		if (strcmp(dp->d_name, ".") == 0 ||
		    strcmp(dp->d_name, "..") == 0) {
			pthread_mutex_lock(&mtx_found);
			found++;
				pthread_mutex_unlock(&mtx_found);
		}
	}

	free(dp);

	pthread_exit(NULL);
}
