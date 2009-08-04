#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main(void)
{
	/*
	 * The `utsname' structure must be defined, including at least
	 * the following members.
	 */
	struct utsname un;

	(void)un.sysname;	/* Name of this implementation of the operating
				   system. */
	(void)un.nodename;	/* Name of this node within the communications
				   network to which this node is attached,
				   if any. */
	(void)un.release;	/* Current release level of this
				   implementation. */
	(void)un.version;	/* Current version level of this release. */
	(void)un.machine;	/* Name of the hardware type on which the system
				   is running. */

	/* We expect this simple call to succeed.
	 * POSIX doesn't define any required errnos, but various implementations
	 * may provide their own.
	 */
	assert(uname(&un) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
