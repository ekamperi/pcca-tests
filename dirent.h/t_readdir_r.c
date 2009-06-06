/* Solaris needs this for bringing in the standard readdir_r() prototype. */
#ifdef __sun__
#define	_POSIX_PTHREAD_SEMANTICS
#endif

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
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
	struct dirent dentry;
	struct dirent *res;

	dirp = (DIR *)arg;

	for (;;) {
		assert(readdir_r(dirp, &dentry, &res) == 0);

		/* Check if we have reached the end of the stream. */
		if (res == NULL)
			break;

		if (dentry.d_type == DT_DIR) {
			if (strcmp(dentry.d_name, ".") == 0 ||
			    strcmp(dentry.d_name, "..") == 0) {
				pthread_mutex_lock(&mtx_found);
				found++;
				pthread_mutex_unlock(&mtx_found);
			}
		}

        }

	pthread_exit(NULL);
}
