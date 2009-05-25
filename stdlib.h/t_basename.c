#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *str[][2] = {{"/usr/lib", "lib"},
			  {"/usr/", "usr"},
			  {"/", "/"},
			  {"///", "/"},
			  {"//usr//lib//", "lib"},
			  {"", "."},
			  {NULL, "."}};

	assert(strcmp(basename(str[0][0]), str[0][1]) == 0);
	assert(strcmp(basename(str[1][0]), str[1][1]) == 0);
        assert(strcmp(basename(str[2][0]), str[2][1]) == 0);
        assert(strcmp(basename(str[3][0]), str[3][1]) == 0);
        assert(strcmp(basename(str[4][0]), str[4][1]) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
