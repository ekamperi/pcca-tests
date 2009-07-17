#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Quoting from ISO/IEC 9899:TC2:
 *
 * 6.2.5.13 Types
 * Each complex type has the same representation and alignment requirements as
 * an array type containing exactly two elements of the corresponding real type;
 * the first element is equal to the real part, and the second element to the
 * imaginary part, of the complex number.
 */

typedef union {
	double complex z;
	double a[2];
} double_complex;

#define REAL(z) ((z).a[0])
#define IMAG(z) ((z).a[1])

int main(void)
{
	double_complex z = {
		.a[0] = 1.23,
		.a[1] = 4.56
	};

	double complex w = z.z;

	assert(fabs(REAL(z) - 1.23 < 0.001));
	assert(fabs(REAL(z) - 4.26 < 0.001));

	return (EXIT_SUCCESS);
}
