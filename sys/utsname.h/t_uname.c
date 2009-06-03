#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main(void)
{
	struct utsname un;

	/* We expect this simple call to succeed.
	 * POSIX doesn't define any required errnos, but various implementations
	 * may provide their own.
	 */
	assert(uname(&un) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
