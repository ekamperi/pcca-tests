/*
 * Copyright (c) 2009, Stathis Kamperis
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The following symbolic constants must have distinct values.
	 * Undefined symbols will be caught by symgen.pl, so don't be
	 * too harsh here.
	 */

/* F_OK -- 6 comparisons */
#if defined(F_OK) && defined(R_OK)
	assert(F_OK != R_OK);
#endif

#if defined(F_OK) && defined(W_OK)
	assert(F_OK != W_OK);
#endif

#if defined(F_OK) && defined(X_OK)
	assert(F_OK != X_OK);
#endif

#if defined(F_OK) && defined(R_OK) && defined(W_OK)
	assert(F_OK != (R_OK|W_OK));
#endif

#if defined(F_OK) && defined(R_OK) && defined(X_OK)
	assert(F_OK != (R_OK|X_OK));
#endif

#if defined(F_OK) && defined(R_OK) && defined(W_OK) && defined(X_OK)
	assert(F_OK != (R_OK|W_OK|X_OK));
#endif


/* R_OK -- 5 comparisons */
#if defined(R_OK) && defined(W_OK)
	assert(R_OK != W_OK);
#endif

#if defined(R_OK) && defined(X_OK)
	assert(R_OK != X_OK);
#endif

#if defined(R_OK) && defined(W_OK)
	assert(R_OK != (R_OK|W_OK));
#endif

#if defined(R_OK) && defined(X_OK)
	assert(R_OK != (R_OK|X_OK));
#endif

#if defined(R_OK) && defined(W_OK) && defined(X_OK)
	assert(R_OK != (R_OK|W_OK|X_OK));
#endif

/* W_OK -- 4 comparisons */
#if defined(W_OK) && defined(X_OK)
        assert(W_OK != X_OK);
#endif

#if defined(W_OK) && defined(R_OK)
        assert(W_OK != (R_OK|W_OK));
#endif

#if defined(W_OK) && defined(R_OK) && defined(X_OK)
        assert(W_OK != (R_OK|X_OK));
#endif

#if defined(W_OK) && defined(R_OK) && defined(X_OK)
        assert(W_OK != (R_OK|W_OK|X_OK));
#endif


/* X_OK -- 3 comparisons */
#if defined(X_OK) && defined(R_OK) && defined(W_OK)
        assert(X_OK != (R_OK|W_OK));
#endif

#if defined(X_OK) && defined(R_OK)
        assert(X_OK != (R_OK|X_OK));
#endif

#if defined(X_OK) && defined(R_OK) && defined(W_OK)
        assert(X_OK != (R_OK|W_OK|X_OK));
#endif

/* R_OK|W_OK -- 2 comparisons */
#if defined(R_OK) && defined(W_OK) && defined(X_OK)
        assert((R_OK|W_OK) != (R_OK|X_OK));
#endif

#if defined(R_OK) && defined(W_OK) && defined(X_OK)
        assert((R_OK|W_OK) != (R_OK|W_OK|X_OK));
#endif


/* R_OK|X_OK -- 1 comparison */
#if defined(R_OK) && defined(W_OK) && defined(X_OK)
        assert((R_OK|X_OK) != (R_OK|W_OK|X_OK));
#endif

/* R_OK|W_OK|X_OK -- none comparison */


	/*
	 * The following symbolic constants must have distinct values.
	 * Undefined symbols will be caught by symgen.pl, so don't be
	 * too harsh here.
	 */
#if defined(SEEK_CUR) && defined(SEEK_END)
	assert(SEEK_CUR != SEEK_END);
#endif

#if defined(SEEK_CUR) && defined(SEEK_SET)
	assert(SEEK_CUR != SEEK_SET);
#endif

#if defined(SEEK_END) && defined(SEEK_SET)
	assert(SEEK_END != SEEK_SET);
#endif

	printf("passed\n");

	return (EXIT_SUCCESS);
}
