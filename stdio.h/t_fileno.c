#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;

	/* Get the file descriptors of the standard streams. */
	assert(fileno(stdin) != -1);
	assert(fileno(stdout) != -1);
	assert(fileno(stderr) != -1);

	/* Open file. */
	fp = fopen("sandbox/file777", "r");
	assert(fp != NULL);

	/* And get the associated descriptor. */
	assert(fileno(fp) != -1);

	/* We are done -- close file. */
	assert(fclose(fp) != EOF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
