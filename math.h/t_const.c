#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * According to C99 standard, HUGE_VAL, HUGE_VALF, HUGE_VALL, INFINITY, and NAN
 * should expand to constant expressions. If they are, then they can be used
 * as initializer elements. Otherwise, this test case will fail to build.
 */

#ifdef HUGE_VAL
double a = HUGE_VAL;
#endif

#ifdef HUGE_VALF
double b = HUGE_VALF;
#endif

#ifdef HUGE_VALL
double c = HUGE_VALL;
#endif

#ifdef INFINITY
double d = INFINITY;
#endif

#ifdef NAN
double e = NAN;
#endif

int
main(void)
{
	printf("passed\n");

	return(EXIT_SUCCESS);
}
