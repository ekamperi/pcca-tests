#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	float xf;
	double xd;
	long double xld;

	/*
	 * 7.12.3.6
	 * NaNs, zeros, and infinities have a sign bit.
	 */
#ifdef	NAN
	xf = NAN;	(void)signbit(xf);
	xd = NAN;	(void)signbit(xd);
	xld = NAN;	(void)signbit(xld);
#endif	/* ! NAN */

	/* If zero is unsigned, it is treated as positive. */
	xf = 0.0;	assert(signbit(xf) == 0);
	xd = 0.0;	assert(signbit(xd) == 0);
	xld = 0.0;	assert(signbit(xld) == 0);

	xf = -0.0;	assert(signbit(xf) != 0);
	xd = -0.0;	assert(signbit(xd) != 0);
	xld = -0.0;	assert(signbit(xld) != 0);

	/* INFINITY expands to a positive expression. */
#ifdef INFINITY
	xf = INFINITY;	assert(signbit(xf) == 0);
	xd = INFINITY;	assert(signbit(xd) == 0);
	xld = INFINITY;	assert(signbit(xld) == 0);
#endif	/* ! INFINITY */

	/*
	 * 7.1.2.3
	 * The following constants, if available, are all positive.
	 */
#ifdef	HUGE_VAL
	xd = HUGE_VAL;
	assert(signbit(xld) == 0);
#endif	/* ! HUGE_VAL */

#ifdef	HUGE_VALF
	xf = HUGE_VALF;
	assert(signbit(xf) == 0);
#endif	/* ! HUGE_VALF */

#ifdef	HUGE_VALL
	xld = HUGE_VALL;
	assert(signbit(xld) == 0);
#endif	/* ! HUVE_VALL */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
