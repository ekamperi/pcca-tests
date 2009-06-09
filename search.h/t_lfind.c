#include <assert.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function prototypes. */
int mystrcmp(const void *s1, const void *s2);

int main(void)
{
	const char *array[] = { "this", "is", "an", "array", "with", "words" };
	size_t i, n, n_orig;
	const char *key;

	/* Number of elements in array. */
	n = sizeof(array) / sizeof(*array);
	n_orig = n;

	for (i = 0; i < n; i++) {
		/* What key to search for. */
		key = array[i];

		assert(lfind(&key, array, &n, sizeof(char *), mystrcmp)
		    != NULL);
	}

	/* Key doesn't exist in array. */
	key = "nonexistentkey";
	assert(lfind(&key, array, &n, sizeof(char *), mystrcmp) == NULL);

	/*
	 * Just a sanity check that lfind doesn't alter the number of elements.
	 * (lsearch which does, increments the integer passed to it)
	 */
	assert(n == n_orig);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

int mystrcmp(const void *s1, const void *s2)
{
#if 0
	printf("s1 = %s\ts2 = %s\n",
	    *(const char **)s1,
	    *(const char **)s2);
#endif

	return (strcmp(*(const char **)s1, *(const char **)s2));
}
