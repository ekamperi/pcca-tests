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

#define _XOPEN_SOURCE 600

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct psxentry {
	const char *psx_desc;
	int psx_constant;
	int psx_minval;
} psxtable[] = {
	/*
	 * POSIX symbolic constants
	 */
#ifdef	_POSIX_AIO_LISTIO_MAX
	{ "_POSIX_AIO_LISTIO_MAX",	_POSIX_AIO_LISTIO_MAX,		2    },
#endif
#ifdef	_POSIX_AIO_MAX
	{ "_POSIX_AIO_MAX",		_POSIX_AIO_MAX,			1    },
#endif
#ifdef	_POSIX_ARG_MAX
	{ "_POSIX_ARG_MAX",		_POSIX_ARG_MAX,			4096 },
#endif
#ifdef	_POSIX_CHILD_MAX
	{ "_POSIX_CHILD_MAX" ,		_POSIX_CHILD_MAX,		25   },
#endif
#ifdef	_POSIX_DELAYTIMER_MAX
	{ "_POSIX_DELAYTIMER_MAX",	_POSIX_DELAYTIMER_MAX,		32   },
#endif
#ifdef	_POSIX_HOST_NAME_MAX
	{ "_POSIX_HOST_NAME_MAX",	_POSIX_HOST_NAME_MAX,		255  },
#endif
#ifdef	_POSIX_LINK_MAX
	{ "_POSIX_LINK_MAX",		_POSIX_LINK_MAX,		8    },
#endif
#ifdef	_POSIX_LOGIN_NAME_MAX
	{ "_POSIX_LOGIN_NAME_MAX",	_POSIX_LOGIN_NAME_MAX,		9    },
#endif
#ifdef	_POSIX_MAX_CANON
	{ "_POSIX_MAX_CANON",		_POSIX_MAX_CANON,		255  },
#endif
#ifdef	_POSIX_MAX_INPUT
	{ "_POSIX_MAX_INPUT",		_POSIX_MAX_INPUT,		255  },
#endif
#ifdef	_POSIX_MQ_OPEN_MAX
	{ "_POSIX_MQ_OPEN_MAX",		_POSIX_MQ_OPEN_MAX,		8    },
#endif
#ifdef	_POSIX_MQ_PRIO_MAX
	{ "_POSIX_MQ_PRIO_MAX",		_POSIX_MQ_PRIO_MAX,		32   },
#endif
#ifdef	_POSIX_NAME_MAX
	{ "_POSIX_NAME_MAX",		_POSIX_NAME_MAX,		9    },
#endif
#ifdef	_POSIX_NGROUPS_MAX
	{ "_POSIX_NGROUPS_MAX",		_POSIX_NGROUPS_MAX,		8    },
#endif
#ifdef	_POSIX_OPEN_MAX
	{ "_POSIX_OPEN_MAX",		_POSIX_OPEN_MAX,		20   },
#endif
#ifdef	_POSIX_PATH_MAX
	{ "_POSIX_PATH_MAX",		_POSIX_PATH_MAX,		256  },
#endif
#ifdef	_POSIX_PIPE_BUF
	{ "_POSIX_PIPE_BUF",		_POSIX_PIPE_BUF,		512  },
#endif
#ifdef	_POSIX_RE_DUP_MAX
	{ "_POSIX_RE_DUP_MAX",		_POSIX_RE_DUP_MAX,		255  },
#endif
#ifdef	_POSIX_RTSIG_MAX
	{ "_POSIX_RTSIG_MAX",		_POSIX_RTSIG_MAX,		8    },
#endif
#ifdef	_POSIX_SEM_NSEMS_MAX
	{ "_POSIX_SEM_NSEMS_MAX",	_POSIX_SEM_NSEMS_MAX,		256  },
#endif
#ifdef	_POSIX_SEM_VALUE_MAX
	{ "_POSIX_SEM_VALUE_MAX",	_POSIX_SEM_VALUE_MAX,		32767},
#endif
#ifdef	_POSIX_SIGQUEUE_MAX
	{ "_POSIX_SIGQUEUE_MAX",	_POSIX_SIGQUEUE_MAX,		32   },
#endif
#ifdef	_POSIX_SSIZE_MAX
	{ "_POSIX_SSIZE_MAX",		_POSIX_SSIZE_MAX,		32767},
#endif
#ifdef	_POSIX_STREAM_MAX
	{ "_POSIX_STREAM_MAX",		_POSIX_STREAM_MAX,		8    },
#endif
#ifdef	_POSIX_SS_REPL_MAX
	{ "_POSIX_SS_REPL_MAX",		_POSIX_SS_REPL_MAX,		4    },
#endif
#ifdef	_POSIX_SYMLINK_MAX
	{ "_POSIX_SYMLINK_MAX",		_POSIX_SYMLINK_MAX,		255  },
#endif
#ifdef	_POSIX_SYMLOOP_MAX
	{ "_POSIX_SYMLOOP_MAX",		_POSIX_SYMLOOP_MAX,		8    },
#endif
#ifdef	_POSIX_THREAD_DESTRUCTOR_ITERATIONS
	{ "_POSIX_THREAD_DESTRUCTOR_ITERATIONS",
	  _POSIX_THREAD_DESTRUCTOR_ITERATIONS,				4    },
#endif
#ifdef	_POSIX_THREAD_KEYS_MAX
	{ "_POSIX_THREAD_KEYS_MAX",	_POSIX_THREAD_KEYS_MAX,		128  },
#endif
#ifdef	_POSIX_THREAD_THREADS_MAX
	{ "_POSIX_THREAD_THREADS_MAX",	_POSIX_THREAD_THREADS_MAX,	64   },
#endif
#ifdef	_POSIX_TIMER_MAX
	{ "_POSIX_TIMER_MAX",		_POSIX_TIMER_MAX,		32   },
#endif
#ifdef	_POSIX_TRACE_EVENT_NAME_MAX
	{ "_POSIX_TRACE_EVENT_NAME_MAX",_POSIX_TRACE_EVENT_NAME_MAX,	30   },
#endif
#ifdef	_POSIX_TRACE_NAME_MAX
	{ "_POSIX_TRACE_NAME_MAX",	_POSIX_TRACE_NAME_MAX,		8    },
#endif
#ifdef	_POSIX_TRACE_SYS_MAX
	{ "_POSIX_TRACE_SYS_MAX",	_POSIX_TRACE_SYS_MAX,		8    },
#endif
#ifdef	_POSIX_TRACE_USER_EVENT_MAX
	{ "_POSIX_TRACE_USER_EVENT_MAX",_POSIX_TRACE_USER_EVENT_MAX,	32   },
#endif
#ifdef	_POSIX_TTY_NAME_MAX
	{ "_POSIX_TTY_NAME_MAX",	_POSIX_TTY_NAME_MAX,		9    },
#endif
#ifdef	_POSIX_TZNAME_MAX
	{ "_POSIX_TZNAME_MAX",		_POSIX_TZNAME_MAX,		6    },
#endif
#ifdef	_POSIX2_BC_BASE_MAX
	{ "_POSIX2_BC_BASE_MAX",	_POSIX2_BC_BASE_MAX,		99   },
#endif
#ifdef	_POSIX2_BC_DIM_MAX
	{ "_POSIX2_BC_DIM_MAX",		_POSIX2_BC_DIM_MAX,		2048 },
#endif
#ifdef	_POSIX2_BC_SCALE_MAX
	{ "_POSIX2_BC_SCALE_MAX",	_POSIX2_BC_SCALE_MAX,		99   },
#endif
#ifdef	_POSIX2_BC_STRING_MAX
	{ "_POSIX2_BC_STRING_MAX",	_POSIX2_BC_STRING_MAX,		1000 },
#endif
#ifdef	_POSIX2_CHARCLASS_NAME_MAX
	{ "_POSIX2_CHARCLASS_NAME_MAX",	_POSIX2_CHARCLASS_NAME_MAX,	14   },
#endif
#ifdef	_POSIX2_COLL_WEIGHTS_MAX
	{ "_POSIX2_COLL_WEIGHTS_MAX",	_POSIX2_COLL_WEIGHTS_MAX,	2    },
#endif
#ifdef	_POSIX2_EXPR_NEST_MAX
	{ "_POSIX2_EXPR_NEST_MAX",	_POSIX2_EXPR_NEST_MAX,		32   },
#endif
#ifdef	_POSIX2_LINE_MAX
	{ "_POSIX2_LINE_MAX",		_POSIX2_LINE_MAX,		2048 },
#endif
#ifdef	_POSIX2_RE_DUP_MAX
	{ "_POSIX2_RE_DUP_MAX",		_POSIX2_RE_DUP_MAX,		255  },
#endif
#ifdef	_XOPEN_IOV_MAX
	{ "_XOPEN_IOV_MAX",		_XOPEN_IOV_MAX,			16   },
#endif
#ifdef	_XOPEN_NAME_MAX
	{ "_XOPEN_NAME_MAX",		_XOPEN_NAME_MAX,		255  },
#endif
#ifdef	_XOPEN_PATH_MAX
	{ "_XOPEN_PATH_MAX",		_XOPEN_PATH_MAX,		1024 },
#endif

	/*
	 * Other invariant values
	 */
#ifdef	NL_ARGMAX
	{ "NL_ARGMAX",			NL_ARGMAX,			9    },
#endif
#ifdef	NL_LANGMAX
	{ "NL_LANGMAX",			NL_LANGMAX,			14   },
#endif
#ifdef	NL_MSGMAX
	{ "NL_MSGMAX",			NL_MSGMAX,			32767},
#endif
#ifdef	NL_SETMAX
	{ "NL_SETMAX",			NL_SETMAX,			255  },
#endif
#ifdef	NL_TEXTMAX
#ifdef	_POSIX2_LINE_MAX
	{ "NL_TEXTMAX",			NL_TEXTMAX,	     _POSIX2_LINE_MAX},
#endif
#endif
#ifdef	NZERO
	{ "NZERO",			NZERO,				20   },
#endif
	{ NULL,				-1,				-1   }
};

int
main(void)
{
	const struct psxentry *p;
	int failed = 0;

	for (p = psxtable; p != NULL; p++) {
		if (p->psx_desc == NULL && p->psx_constant == -1
		    && p->psx_minval == -1)
			break;

		if (p->psx_constant < p->psx_minval) {
			fprintf(stderr, "%s: min: %d got: %d\n", p->psx_desc,
			    p->psx_minval, p->psx_constant);
			failed = 1;
		}
	}

	assert(failed == 0);

	printf("passed (%d symbols checked)\n",
	    sizeof(psxtable) / sizeof(psxtable[0]));

	return (EXIT_SUCCESS);
}
