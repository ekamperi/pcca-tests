#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `if_nameindex' structure must be defined, that includes
	 * at least the following members.
	 */
	struct if_nameindex ifni;

	(void)ifni.if_index;	/* Numeric index of the interface. */
	(void)ifni.if_name;	/* Null-terminated name of the interface. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
