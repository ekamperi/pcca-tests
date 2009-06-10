#include <assert.h>
#include <limits.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define	KEYSIZE	10	/* Size of the key. */
#define	NITEMS	10000	/* Number of items to insert into the table. */

/* This is the actual data that are stored in the table (except for the key). */
struct payload {
	int x, y, z;
};

int main(void)
{
	/* Space to store keys. */
	char key_space[NITEMS * KEYSIZE];

	/* Space to store the actual payload. */
	struct payload payload_space[NITEMS];

	char *pks= key_space;
	struct payload *pps = payload_space;
	ENTRY item, *pfound;
	char target[KEYSIZE];
	size_t i;

	/* Initialize random number generator. */
	srand(time(NULL));

	/*
	 * Create hash table.
	 * (We can only create one hash table. But we may destroy the current
	 * and create a new one.)
	 */
	assert(hcreate(NITEMS) != 0);

	/* Populate hash table with items. */
	for (i = 0; i < NITEMS; i++) {

		/* Yes, I'm aware that this doesn't give always good results. */
		pps->x = rand() % INT_MAX;
		pps->y = rand() % INT_MAX;
		pps->z = pps->x ^ pps->y;

		/* Construct a key. */
		snprintf(pks, KEYSIZE, "%d%d%d", i, i+1, i+2);

		item.key = pks;
		item.data = pps;

		/* Advance the pointers in the key/payload space. */
		pks += strlen(pks) + 1;
		pps++;

		/*
		 * Insert item into table.
		 * hsearch(, ENTER) shall return NULL only if the table is full,
		 * which clearly isn't the case here since we insert exactly
		 * `NITEMS'.
		 * Caveat: the specs allow the implementation to adjust upward
		 * the size of the table.
		 */
		assert(hsearch(item, ENTER) != NULL);
	}

	/* Verify inserted items. */
	for (i = 0; i < NITEMS; i++) {
		snprintf(target, KEYSIZE, "%d%d%d", i, i+1, i+2);

		item.key = target;

		assert((pfound = hsearch(item, FIND)) != NULL);
		assert((((struct payload *)pfound->data)->x ^
			((struct payload *)pfound->data)->y) ==
		    ((struct payload *)pfound->data)->z);
	}

	/* Destroy hash table. */
	hdestroy();

	printf("passed\n");

	return (EXIT_SUCCESS);
}
