#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int supported1 = 0;	/* Via sysconf(3). */
	int supported2 = 0;	/* Via symbol constant definition. */
	int rv;

#ifdef _SC_MYSYMBOL
	errno = 0;
	rv = sysconf(_SC_MYSYMBOL);
	assert(rv != -1 || errno == 0);

	supported1 = (rv == -1) ? -1 : 1;
#endif

#ifdef _POSIX_MYSYMBOL
	#if (_POSIX_MYSYMBOL - 0L) > 0L
		supported2 = 1;
	#else
		supported2 = -1;
	#endif
#endif

	/* Make sure we don't get contradictory results. */
	assert(supported1 * supported2 != -1);

	/* Make sure that at least one of the query methods works. */
	//assert(supported1 * supported2 != 0);

	printf("passed\n");
}
