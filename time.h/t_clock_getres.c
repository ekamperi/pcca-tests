#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	struct timespec clres;
	int monotonic = 0;

	/*
	 * Get the resolution of the clock.
	 * CLOCK_REALTIME is mandatory.
	 */
	assert(clock_getres(CLOCK_REALTIME, &clres) != -1);

	/* Contrary to CLOCK_MONOTONIC, which is optional. */
#ifdef	_POSIX_MONOTONIC_CLOCK
	errno = 0;
	long rv = sysconf(_SC_MONOTONIC_CLOCK);
	assert(rv != -1 || errno == 0);

	assert(clock_getres(CLOCK_MONOTONIC, &clres) != -1);
	monotonic = 1;
#endif

	if (monotonic == 1)
		printf("passed\n");
	else
		printf("passed (CLOCK_MONOTONIC check skipped)\n");

	return (EXIT_SUCCESS);
}
