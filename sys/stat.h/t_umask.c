#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	mode_t oldmode, oldmode2, oldmode3;

#if defined(S_IRWXU) && defined(S_IRWXG) && defined(S_IRWXO)
	/* Set the file creation mask. */
	oldmode = umask(S_IRWXU | S_IRWXG | S_IRWXO);

	/* Restore the original creation mask. */
	oldmode2 = umask(oldmode);

	/*
	 * After this, oldmode3 must be equal to the very original
	 * creation mask.
	 */
	oldmode3 = umask(oldmode);

	assert(oldmode2 == (S_IRWXU | S_IRWXG | S_IRWXO));
	assert(oldmode3 == oldmode);

	/*
	 * XXX: We should add tests to check whether creation mask is _actually_
	 * honoured by at least: open(), creat(), mkdir(), mkfifo() and
	 * optionally mknod(), mq_open(), sem_open().
	 */

	printf("passed\n");
#else
	printf("passed (critical: umask modification skipped)\n");
#endif

	return (EXIT_SUCCESS);
}
