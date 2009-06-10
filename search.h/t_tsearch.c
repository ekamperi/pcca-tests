#include <assert.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes. */
static int mycmp(const void *, const void *);
static void visitnode(const void *nodep, VISIT order, int level);

/* Global variables. */
int intpool[100];	/* Every integer occupies a position in the pool. */
void *rootp = NULL;	/* The root node of the tree. */

/*
 * `array'           holds the integers that shall be inserted into the tree.
 * `array_preorder'  holds the order of integers in a depth-first search.
 * `array_postorder' holds the order of integers in a left-right traversal.
 * `array_endorder'
 * `array_leaf'      holds the leafs of the tree.
 */
int array[]           = { -2, 7, 11, 0, 26, 4, 5, 1, 12, -9, -6, 20, 101, -33 };
int array_preorder[]  = { 7, 0, -6, -9, 4, 12, 26 };
int array_postorder[] = { -9, -6, 0, 4, 7, 12, 26 };
int array_endorder[]  = { -9, -6, 4, 0, 26, 12, 7 };
int array_leaf[]      = { -33, -2, 1, 5, 11, 20, 101 };

int *p_array_preorder  = array_preorder;
int *p_array_postorder = array_postorder;
int *p_array_endorder  = array_endorder;
int *p_array_leaf      = array_leaf;

int main(void)
{
	size_t i, n;
	int *intp = intpool;

	/* Number of items that shall be inserted. */
	n = sizeof(array) / sizeof(array[0]);

	/* Populate the binary tree. */
	for (i = 0; i < n; i++) {
		/* Assign the right value in integer. */
		*intp = array[i];

		/* Insert the node into the tree. */
		assert(tsearch(intp, &rootp, mycmp) != NULL);

		/* Advance pointer. */
		intp++;
	}

	/* Verify that all items are in the tree. */
	for (i = 0; i < n; i++) {
		intp = &array[i];
		assert(**((int **)tfind(intp, &rootp, mycmp)) == array[i]);
	}

	/* Traverse tree. */
	twalk(rootp, visitnode);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static int
mycmp(const void *px, const void *py)
{
	int x = *(int *)px;
	int y = *(int *)py;

	/*
	 * POSIX expects an integer number less than, equal to, or greater
	 * than 0. So we don't have to return -1, +1 necessarily.
	 */

	return (x - y);
}

static void
visitnode(const void *nodep, VISIT order, int level)
{
        const int *p = *(const int **)nodep;

	switch(order) {
	case preorder:
		/* depth-first */
		assert(*p == *p_array_preorder);
		p_array_preorder++;
		break;
	case postorder:
		/* left-to-right traversal */
		assert(*p == *p_array_postorder);
		p_array_postorder++;
		break;
	case endorder:
		/* node traversed 3rd time. */
		assert(*p == *p_array_endorder);
		p_array_endorder++;
		break;
	case leaf:
		/* node is a leaf */
		assert(*p == *p_array_leaf);
		p_array_leaf++;
		break;
	default:
		break;
	}
}

