/*	$OpenBSD: strtodtest.c,v 1.1 2006/09/29 11:00:24 otto Exp $	*/
/* Public domain, Otto Moerbeek <otto@drijf.net>, 2006. */

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Checks if strtod() reports underflow.
 */

int
main(void)
{
	const char *tmp="0.0000000000000000000000000000000000000000000000000000"
	    "000000000000000000000000000000000000000000000000000000000000000000"
	    "000000000000000000000000000000000000000000000000000000000000000000"
	    "000000000000000000000000000000000000000000000000000000000000000000"
	    "000000000000000000000000000000000000000000000000000000000000000000"
	    "000000000000000000000000000000000000000000000000000000000000000000"
	    "000000000002";
	double d;

	d = strtod(tmp, NULL);
	assert(d == 0 && errno == ERANGE);    /* XXX: Is it safe to do == 0 ? */

	printf("passed\n");

	return (EXIT_SUCCESS);
}