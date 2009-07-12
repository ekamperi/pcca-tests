#define _XOPEN_SOURCE 600

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	long id;

	id = gethostid();

	printf("passed\n");

	return (EXIT_SUCCESS);
}
