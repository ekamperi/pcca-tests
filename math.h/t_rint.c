#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*                                                                                                                     
 * The rint*() functions return the integral value (represented as a                                                   
 * double) nearest x in the direction of the current rounding mode.                                                    
 *                                                                                                                     
 * POSIX says that the rounding mode is implementation-defined, so                                                     
 * that leaves us in the dark, I guess.                                                                                
 */

struct tentry {
	double x;       /* Input */
	double y;       /* rint output */
} ttable[] = {
	{   1.010,     1.000 },
	{  -1.010,    -1.000 },
	{   2.411,     2.000 },
	{  -2.411,    -2.000 }, 
	{   3.999,     4.000 },
	{  -3.999,    -4.000 },
	{   9.997,    10.000 },
	{  -9.997,   -10.000 },
	{  101.005,  101.000 }, 
	{ -101.005, -101.000 },
	{  507.777,  508.000 },
	{ -507.777, -508.000 }
};

int main(void)
{
	size_t i;

        for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++)
                assert(fabs(rint(ttable[i].x) - ttable[i].y) < 0.001);
	
	/* If x is NaN, a NaN shall be returned. */
	assert(isnan(rint(nan(""))) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
