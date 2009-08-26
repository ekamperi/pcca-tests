/*	$OpenBSD: longjmp.c,v 1.4 2002/02/18 11:27:45 art Exp $	*/
/*
 *	Artur Grabowski <art@openbsd.org>, 2002 Public Domain.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

jmp_buf buf;

/*
 * When longjmp is passed the incorrect arg (0), it should translate it into
 * something better.
 */
int main(void)
{
	struct rlimit rl;
	int (*sj)(jmp_buf);
	void (*lj)(jmp_buf, int);
	volatile int expect, rv;

	/* The rlimit is here in case we start spinning. */
	rl.rlim_cur = 2;
	rl.rlim_max = 2;
	assert(setrlimit(RLIMIT_CPU, &rl) == 0);

	/* Check setjmp/longjmp first. */
	sj = setjmp;
	lj = longjmp;

	expect = 0;
	rv = (*sj)(buf);
	assert(rv != 0 || expect == 0);
	if (expect == 0) {
		expect = -1;
		(*lj)(buf, 0);
	}

	expect = 0;
	rv = (*sj)(buf);
	assert(rv == expect);
	if (expect < 1000)
		(*lj)(buf, expect += 2);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
