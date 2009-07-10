#define _XOPEN_SOURCE 600	/* We need this for the `LEGACY'
				   _CS_XXX symbols. */
#include <assert.h>
#include <errno.h>
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int table[] = {
#ifdef	_CS_PATH
	_CS_PATH,
#endif
#ifdef	_CS_POSIX_V6_ILP32_OFF32_CFLAGS
	_CS_POSIX_V6_ILP32_OFF32_CFLAGS,
#endif
#ifdef	_CS_POSIX_V6_ILP32_OFF32_LDFLAGS
	_CS_POSIX_V6_ILP32_OFF32_LDFLAGS,
#endif
#ifdef	_CS_POSIX_V6_ILP32_OFF32_LIBS
	_CS_POSIX_V6_ILP32_OFF32_LIBS,
#endif
#ifdef	_CS_POSIX_V6_ILP32_OFFBIG_CFLAGS
	_CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,
#endif
#ifdef	_CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS
	_CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,
#endif
#ifdef	_CS_POSIX_V6_ILP32_OFFBIG_LIBS
	_CS_POSIX_V6_ILP32_OFFBIG_LIBS,
#endif
#ifdef	_CS_POSIX_V6_LP64_OFF64_CFLAGS
	_CS_POSIX_V6_LP64_OFF64_CFLAGS,
#endif
#ifdef	_CS_POSIX_V6_LP64_OFF64_LDFLAGS
	_CS_POSIX_V6_LP64_OFF64_LDFLAGS,
#endif
#ifdef	_CS_POSIX_V6_LP64_OFF64_LIBS
	_CS_POSIX_V6_LP64_OFF64_LIBS,
#endif
#ifdef	_CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS
	_CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,
#endif
#ifdef	_CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS
	_CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,
#endif
#ifdef	_CS_POSIX_V6_LPBIG_OFFBIG_LIBS
	_CS_POSIX_V6_LPBIG_OFFBIG_LIBS,
#endif
#ifdef	_CS_POSIX_V6_WIDTH_RESTRICTED_ENVS
	_CS_POSIX_V6_WIDTH_RESTRICTED_ENVS,
#endif
	/* The following are marked as `LEGACY' in Issue 6. */
#ifdef	_CS_XBS5_ILP32_OFF32_CFLAGS
	_CS_XBS5_ILP32_OFF32_CFLAGS, 
#endif
#ifdef	_CS_XBS5_ILP32_OFF32_LDFLAGS
	_CS_XBS5_ILP32_OFF32_LDFLAGS, 
#endif
#ifdef	_CS_XBS5_ILP32_OFF32_LIBS
	_CS_XBS5_ILP32_OFF32_LIBS,
#endif
#ifdef	_CS_XBS5_ILP32_OFF32_LINTFLAGS
	_CS_XBS5_ILP32_OFF32_LINTFLAGS, 
#endif
#ifdef	_CS_XBS5_ILP32_OFFBIG_CFLAGS
	_CS_XBS5_ILP32_OFFBIG_CFLAGS,
#endif
#ifdef	_CS_XBS5_ILP32_OFFBIG_LDFLAGS
	_CS_XBS5_ILP32_OFFBIG_LDFLAGS,
#endif
#ifdef	_CS_XBS5_ILP32_OFFBIG_LIBS
	_CS_XBS5_ILP32_OFFBIG_LIBS, 
#endif
#ifdef	_CS_XBS5_ILP32_OFFBIG_LINTFLAGS
	_CS_XBS5_ILP32_OFFBIG_LINTFLAGS, 
#endif
#ifdef	_CS_XBS5_LP64_OFF64_CFLAGS
	_CS_XBS5_LP64_OFF64_CFLAGS, 
#endif
#ifdef	_CS_XBS5_LP64_OFF64_LDFLAGS
	_CS_XBS5_LP64_OFF64_LDFLAGS, 
#endif
#ifdef	_CS_XBS5_LP64_OFF64_LIBS
	_CS_XBS5_LP64_OFF64_LIBS, 
#endif
#ifdef	_CS_XBS5_LP64_OFF64_LINTFLAGS
	_CS_XBS5_LP64_OFF64_LINTFLAGS, 
#endif
#ifdef	_CS_XBS5_LPBIG_OFFBIG_CFLAGS
	_CS_XBS5_LPBIG_OFFBIG_CFLAGS, 
#endif
#ifdef	_CS_XBS5_LPBIG_OFFBIG_LDFLAGS
	_CS_XBS5_LPBIG_OFFBIG_LDFLAGS, 
#endif
#ifdef	_CS_XBS5_LPBIG_OFFBIG_LIBS
	_CS_XBS5_LPBIG_OFFBIG_LIBS,
#endif
#ifdef	_CS_XBS5_LPBIG_OFFBIG_LINTFLAGS
	_CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,
#endif
};

int main(void)
{
	size_t i, len;
	char buf[16384];

	/* Get number of elements symbols defined. */
	len = sizeof(table)/sizeof(table[0]);

	for (i = 0; i < len; i++) {
		/*
		 * If `name' doesn't have a configuration-defined value,
		 * confstr() returns 0 and leaves `errno' unchanged.
		 */
		errno = 0;
		assert(confstr(table[i], buf, sizeof(buf)) != 0 || errno == 0);
	}

	/* The value of `name' is invalid. */
	assert(confstr(-INT_MAX, buf, sizeof(buf)) == 0
	    && errno == EINVAL);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
