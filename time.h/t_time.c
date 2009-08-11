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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{

	/*
	 * The `tm' structure must be defined, including at least
	 * the following members.
	 */
	struct tm tm;

	(void)tm.tm_sec;	/* Seconds [0,60]. */
	(void)tm.tm_min;	/* Minutes [0,59]. */
	(void)tm.tm_hour;	/* Hour [0,23]. */
	(void)tm.tm_mday;	/* Day of month [1,31]. */
	(void)tm.tm_mon;	/* Month of year [0,11]. */
	(void)tm.tm_year;	/* Years since 1900. */
	(void)tm.tm_wday;	/* Day of week [0,6] (Sunday =0). */
	(void)tm.tm_yday;	/* Day of year [0,365]. */
	(void)tm.tm_isdst;	/* Daylight Savings flag. */

	/*
	 * The `itimerspec' structure must be defined, including at least
	 * the following members.
	 */
	struct itimerspec it;

	(void)it.it_interval;	/* Timer period. */
	(void)it.it_value;	/* Timer expiration. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
