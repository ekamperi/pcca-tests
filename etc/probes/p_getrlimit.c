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

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <sys/resource.h>

struct rlentry {
	const char *rl_desc;
	int rl_name;
} rltable[] = {
#ifdef  RLIMIT_CORE
	{ "RLIMIT_CORE",	RLIMIT_CORE	},
#endif
#ifdef  RLIMIT_CPU
	{ "RLIMIT_CPU",		RLIMIT_CPU	},
#endif
#ifdef  RLIMIT_DATA
	{ "RLIMIT_DATA",	RLIMIT_DATA	},
#endif
#ifdef  RLIMIT_FSIZE
	{ "RLIMIT_FSIZE",	RLIMIT_FSIZE	},
#endif
#ifdef  RLIMIT_NOFILE
	{ "RLIMIT_NOFILE",	RLIMIT_NOFILE	},
#endif
#ifdef  RLIMIT_STACK
	{ "RLIMIT_STACK",	RLIMIT_STACK	},
#endif
#ifdef  RLIMIT_AS
	{ "RLIMIT_AS",		RLIMIT_AS	},
#endif
	{ NULL,			-1		}
};

int main(void)
{
	struct rlimit rlmp;
        const struct rlentry *rle;
	int rv;

	/* Zero out rlimit structure. */
	memset(&rlmp, 0, sizeof(struct rlimit));

        for (rle = rltable; rle != NULL; rle++) {
		if (rle->rl_desc == NULL && rle->rl_name == -1)
			break;

		rv = getrlimit(rle->rl_name, &rlmp);
		if (rv != 0)
			perror("getrlimit");

		printf("desc: %-20s\tcurrent val: %-20ju\thard limit: %-20ju\n",
		    rle->rl_desc,
		    (uintmax_t)rlmp.rlim_cur,
		    (uintmax_t)rlmp.rlim_max);
	}

	return (EXIT_SUCCESS);
}
