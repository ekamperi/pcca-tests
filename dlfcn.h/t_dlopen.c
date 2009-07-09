#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void)
{

	(void)RTLD_LAZY;	/* Relocations are performed at an
				   implementation-defined time. */
	(void)RTLD_NOW;		/* Relocations are performed when the object is
				   loaded. */
	(void)RTLD_GLOBAL;	/* All symbols are available for relocation
				   processing of other modules. */
	(void)RTLD_LOCAL;	/* All symbols are not made. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
