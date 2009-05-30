#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Floating point exceptions. */
#if defined(math_errhandling) && defined(MATH_ERREXCEPT) && \
	   (math_errhandling & MATH_ERREXCEPT)
#include <fenv.h>
#endif

struct tentry {
	const char *desc;
	double (*pf)();
	int nargs;
	double x;
	double y;
} ttable[] = {
	{ "t_acos",  acos,   1,  -2,  /* ignored */ 0 },
	{ "t_acos",  acos,   1,   2,  /* ignored */ 0 },
	{ "t_asin",  asin,   1,  -2,  /* ignored */ 0 },
	{ "t_atan2", atan2,  2,   0,  0               },
	{ "t_acosh", acosh,  1,  -1,  /* ignored */ 0 },
	{ NULL,      NULL,  -1,  -1,  -1 }
};

/* Function prototypes. */
void runtest(const struct tentry *te);

int main(void)
{
	const struct tentry *te;
	pid_t pid;

	for (te = ttable; te != NULL; te++) {
		if (te->desc == NULL && te->pf == NULL && te-> nargs == -1 &&
		    te->x == -1 && te->y == -1)
			break;

		pid = fork();
		assert(pid != -1);

		if (pid == 0) {
			/* We are inside the child. */
			printf("%s ", te->desc);
			fflush(NULL);

			/* Runt the actual test. */
			runtest(te);

			/*
			 * We don't want the child to continue the loop, so break
			 * the circle before it becomes vicious.
			 */
			break;
		} else {
			/* We are inside the parent. */
			int status;
			wait(&status);
		}

	}

	return (EXIT_SUCCESS);
}

void runtest(const struct tentry *te)
{
        int t_errno = 0;        /* Whether errno branch was executed. */
        int t_fp = 0;           /* Whether fp exception branch was executed. */

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
	assert(te->nargs == 1 || te->nargs == 2);
	if (te->nargs == 1)
		te->pf(te->x);
	else
		te->pf(te->x, te->y);

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
}
