#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char *p;

	/* Get login name. */
	p = getlogin();
	assert(p != NULL);

	return (EXIT_SUCCESS);
}
