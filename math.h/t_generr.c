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

/* Floating point exception constant is missing. */
#define FPE_IS_MISSING	(-112233)

#ifdef	FE_INVALID
	#define	MY_FE_INVALID	FE_INVALID
#else
	#define MY_FE_INVALID	FPE_IS_MISSING
#endif


#ifdef	FE_DIVBYZERO
	#define	MY_FE_DIVBYZERO	FE_DIVBYZERO
#else
	#define MY_FE_DIVBYZERO	FPE_IS_MISSING
#endif


#ifdef	FE_OVERFLOW
	#define MY_FE_OVERFLOW	FE_OVERFLOW
#else
	#define MY_FE_OVERFLOW	FPE_IS_MISSING
#endif


#ifdef	FE_UNDERFLOW
	#define MY_FE_UNDERFLOW	FE_UNDERFLOW
#else
	#define MY_FE_UNDERFLOW	FPE_IS_MISSING
#endif

struct tentry {
	const char *desc;
	double (*pf)();
	int nargs;
	double x;
	double y;
	int errcode;	/* errno */
	int fpe;	/* floating point exception */
} ttable[] = {
	{ "t_acos", acos,
	  1, -2, /* ignored */ 0,
	  EDOM, MY_FE_INVALID
	},

	{ "t_acos", acos,
	  1, 2, /* ignored */ 0,
	  EDOM, MY_FE_INVALID
	},

	{ "t_asin", asin,
	  1, -2, /* ignored */ 0,
	  EDOM, MY_FE_INVALID
	},

	{ "t_atan2", atan2,
	  2, 0, 1,
	  ERANGE, MY_FE_UNDERFLOW
	},

	{ "t_acosh", acosh,
	  1, -1, /* ignored */ 0,
	  EDOM, MY_FE_INVALID
	},

	{ "t_atanh", atanh,
	  1, -2, /* ignored */ 0,
	  EDOM,   MY_FE_INVALID
	},

	{ "t_atanh", atanh,
	  1, -1, /* ignored */ 0,
	  ERANGE, MY_FE_DIVBYZERO
	},

	{ "t_log", log,
	  1, -1, /* ignored */ 0,
	  EDOM,   MY_FE_INVALID
	},

	{ "t_log", log,
	  1,   0,  /* ignored */ 0,
	  ERANGE, MY_FE_DIVBYZERO
	},

        { "t_log10", log10,
	  1, -1, /* ignored */ 0,
          EDOM, MY_FE_INVALID
	},

        { "t_log10", log10,
	  1, 0, /* ignored */ 0,
          ERANGE, MY_FE_DIVBYZERO
	},

        { "t_log2", log2,
	  1, -1, /* ignored */ 0,
          EDOM, MY_FE_INVALID
	},

        { "t_log2", log2,
	  1, 0, /* ignored */ 0,
          ERANGE, MY_FE_DIVBYZERO
	},

        { "t_log1p", log1p,
	  1, -2, /* ignored */ 0,
          EDOM, MY_FE_INVALID
	},

        { "t_log1p", log1p,
	  1, -1, /* ignored */ 0,
          ERANGE, MY_FE_DIVBYZERO
	},

#if	(_XOPEN_SOURCE - 0) >= 600
	{ "t_ilogb", ilogb,
	  1, 0, /* ignored */ 0,
	  EDOM, MY_FE_INVALID
	},
#endif

	{ "t_logb", logb,
	  1, 0, /* ignored */ 0,
	  ERANGE, MY_FE_DIVBYZERO
	},

	{ "t_pow", pow,
	  2, -1, 2.34,
	  EDOM, MY_FE_INVALID
	},

	{ "t_pow", pow,
	  2, 0, -1,
	  ERANGE, MY_FE_DIVBYZERO
	},

	{ "t_sqrt", sqrt,
	  1, -1, /* ignored */ 0,
	  EDOM, MY_FE_INVALID
	},

	{ "t_lgamma", lgamma,
	  2, -1, /* ignored */ 0,
	  ERANGE, MY_FE_DIVBYZERO
	},

	{ "t_fmod", fmod,
	  2, 1, 0,
	  EDOM, MY_FE_INVALID
	},

	{ NULL, NULL,
	  -1, -1, -1,
	  -1, -1
	}
};

/* Function prototypes. */
void runtest(const struct tentry *te);

int main(void)
{
	const struct tentry *te;
	pid_t pid;

	for (te = ttable; te != NULL; te++) {
		if (te->desc == NULL && te->pf == NULL && te-> nargs == -1)
			break;

		pid = fork();
		assert(pid != -1);

		if (pid == 0) {
			/* We are inside the child. */
			printf("/math.h/t_generr: %s: ", te->desc);
			fflush(NULL);

			/* Run the actual test. */
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
         * According to POSIX, errno must be set at this point.
         * A note to myself: if math_errhandling & MATH_ERRNO is zero
         * then the specs don't expect errno to be set. So having an
         * implementation update the errno variable isn't mandatory.
	 * Read below for caveat.
         */
        assert(errno == te->errcode);
        t_errno = 1;
#endif

#if defined(math_errhandling) && defined(MATH_ERREXCEPT) && \
        (math_errhandling & MATH_ERREXCEPT)

        /*
         * According to POSIX, the floating point exception shall
         * be raised at this point. Just as before, this isn't required
         * if math_errhandling & MATH_ERREXCEPT is zero.
	 * Read below for caveat.
         */
	if (te->fpe != FPE_IS_MISSING) {
		assert(fetestexcept(te->fpe) != 0);
		t_fp = 1;
	}
#endif

	/*
	 * On error, there must be AT LEAST one non-zero expression among
	 * (math_errhandling & MATH_ERRNO), (math_errhandling & MATH_ERREXCEPT).
	*/
        assert(t_errno != 0 || t_fp != 0);

        printf("passed\t");

        if (t_errno != 0 && t_fp == 0)
                printf("(fp check was skipped)");
        else if (t_errno == 0 && t_fp != 0)
                printf("(errno check was skipped)");

        printf("\n");
}
