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