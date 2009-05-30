#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Floating point exceptions. */
#if defined(math_errhandling) && defined(MATH_ERREXCEPT) && \
	   (math_errhandling & MATH_ERREXCEPT)
#include <fenv.h>
#endif

int main(void)
{
	int t_errno = 0;	/* Whether errno branch was executed. */
	int t_fp = 0;		/* Whether fp exception branch was executed. */

#if defined(math_errhandling) && (math_errhandling & MATH_ERREXCEPT)
	/*
	 * FE_ALL_EXCEPT expands to the bitwise OR of all exception flags.
	 * Clear all of them now, so that we can deduce which ones were
	 * raised later on.
	 */
	feclearexcept(FE_ALL_EXCEPT);
#endif

	/* Simon says we must zero out errno variable. */
	errno = 0;

	/* p0wned */
	sqrt(-1);

#if defined(math_errhandling) && defined(MATH_ERRNO) && \
	(math_errhandling & MATH_ERRNO)

	/*
	 * According to POSIX, errno must be set to EDOM at this point.
	 * A note to myself: if math_errhandling & MATH_ERRNO is zero
	 * then the specs don't expect errno to be set. So having an
	 * implementation update the errno variable isn't mandatory.
	 */
	assert(errno == EDOM);
	t_errno = 1;
#endif

#if defined(math_errhandling) && defined(MATH_ERREXCEPT) && \
	(math_errhandling & MATH_ERREXCEPT)
	
	/*
	 * According to POSIX, the invalid floating point exception shall
	 * be raised at this point. Just as before, this isn't required
	 * if math_errhandling & MATH_ERREXCEPT is zero. BUT, at least one
	 * out of (math_errhandling & MATH_ERRNO) and (math_errhandling &
	 * MATH_ERREXCEPT) but be non-zero according to the standard.
	 */
	assert(fetestexcept(FE_INVALID) != 0);
	t_fp = 1;
#endif

	assert(t_errno != 0 || t_fp != 0);

	printf("passed\t");

	if (t_errno != 0 && t_fp == 0)
		printf("(fp check was skipped)");
	else if (t_errno == 0 && t_fp != 0)
		printf("(errno check was skipped)");

	printf("\n");

	return (EXIT_SUCCESS);
}
