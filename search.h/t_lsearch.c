#include <assert.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function prototypes. */
int mystrcmp(const void *s1, const void *s2);

int main(void)
{
	const char *array[7] = { "this", "is", "an", "array", "with", "words" };
	size_t i, n;
	const char *key;

	/* Number of current elements in array. */
	n = 6;

	for (i = 0; i < n; i++) {
		/* What key to search for. */
		key = array[i];

		assert(lsearch(&key, array, &n, sizeof(char *), mystrcmp)
		    != NULL);
	}

	/* A sanity check that lsearch didn't alter the number of elements.  */
	assert(n == 6);

        /* Key doesn't exist in array, but lsearch() shall appened it. */
        key = "nonexistentkey";
	assert(*(char **)lsearch(&key, array, &n, sizeof(char *), mystrcmp)
	    == key && n == 7);

	/* Seems as if the new element has been inserted. Can lfind() find it ? */
	assert(lfind(&key, array, &n, sizeof(char *), mystrcmp) != NULL);

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
