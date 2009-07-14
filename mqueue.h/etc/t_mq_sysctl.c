#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysctl.h>

int main(void)
{
	const char *sysctlnames[] = {
		"kern.mqueue.mq_def_maxmsg",
		"kern.mqueue.mq_max_msgsize",
		"kern.mqueue.mq_prio_max",
		"kern.mqueue.mq_open_max" };
	int oldval;
	size_t oldsize = sizeof(oldval);
	size_t i;

	/*
	 * For every sysctl variable, read its value.
	 *
	 * In order to just read (ie, not set) the value of a sysctl variable,
	 * we pass NULL, 0 for newp, newlen as described in sysctl(3).
	 */
	for (i = 0; i < sizeof(sysctlnames) / sizeof(char *); i++) {
		assert(sysctlbyname(sysctlnames[i], &oldval, &oldsize, NULL, 0)
		    != -1);
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
