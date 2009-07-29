#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char buf[1024];
	FILE *fp;
	size_t rv;

	/* Open file for reading. */
	fp = fopen("sandbox/file777", "r");
	assert(fp != NULL);

	/*  Read up until the end of file. */
	while(!feof(fp)) {
		rv = fread(buf, sizeof(buf), 1, fp);
		assert(rv == 1 || feof(fp));
	}

	/* This is paranoid. */
	assert(feof(fp));

	/* Clear the end of file indicator. */
	clearerr(fp);
	assert(!feof(fp));

	/* XXX: What about any other error indicators ? */

	/* We are done -- close file. */
	assert(fclose(fp) != EOF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
