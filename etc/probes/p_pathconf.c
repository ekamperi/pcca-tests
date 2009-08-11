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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    /* strerror(3) */
#include <unistd.h>

struct pcentry {
	const char *pc_desc;
	int pc_name;
} pctable[] = {
#ifdef	_PC_FILESIZEBITS
	{ "_PC_FILESIZEBITS",		_PC_FILESIZEBITS	},
#endif
#ifdef	_PC_LINK_MAX
	{ "_PC_LINK_MAX",		_PC_LINK_MAX		},
#endif
#ifdef	_PC_MAX_CANON
	{ "_PC_MAX_CANON",		_PC_MAX_CANON		},
#endif
#ifdef	_PC_MAX_INPUT
	{ "_PC_MAX_INPUT",		_PC_MAX_INPUT		},
#endif
#ifdef	_PC_NAME_MAX
	{ "_PC_NAME_MAX",		_PC_NAME_MAX		},
#endif
#ifdef	_PC_PATH_MAX
	{ "_PC_PATH_MAX",		_PC_PATH_MAX		},
#endif
#ifdef	_PC_PIPE_BUF
	{ "_PC_PIPE_BUF",		_PC_PIPE_BUF		},
#endif
#ifdef	_PC_2_SYMLINKS
	{ "_PC_2_SYMLINKS",		_PC_2_SYMLINKS		},
#endif
#ifdef	_PC_ALLOC_SIZE_MIN
	{ "_PC_ALLOC_SIZE_MIN",		_PC_ALLOC_SIZE_MIN	},
#endif
#ifdef	_PC_REC_INCR_XFER_SIZE
	{ "_PC_REC_INCR_XFER_SIZE",	_PC_REC_INCR_XFER_SIZE	},
#endif
#ifdef	_PC_REC_MAX_XFER_SIZE
	{ "_PC_REC_MAX_XFER_SIZE",	_PC_REC_MAX_XFER_SIZE	},
#endif
#ifdef	_PC_REC_MIN_XFER_SIZE
	{ "_PC_REC_MIN_XFER_SIZE",	_PC_REC_MIN_XFER_SIZE	},
#endif
#ifdef	_PC_REC_XFER_ALIGN
	{ "_PC_REC_XFER_ALIGN",		_PC_REC_XFER_ALIGN	},
#endif
#ifdef	_PC_SYMLINK_MAX
	{ "_PC_SYMLINK_MAX",		_PC_SYMLINK_MAX		},
#endif
#ifdef	_PC_CHOWN_RESTRICTED
	{ "_PC_CHOWN_RESTRICTED",	_PC_CHOWN_RESTRICTED	},
#endif
#ifdef	_PC_NO_TRUNC
	{ "_PC_NO_TRUNC",		 _PC_NO_TRUNC		},
#endif
#ifdef	_PC_VDISABLE
	{ "_PC_VDISABLE",		_PC_VDISABLE		},
#endif
#ifdef	_PC_ASYNC_IO
	{ "_PC_ASYNC_IO",		_PC_ASYNC_IO		},
#endif
#ifdef	_PC_PRIO_IO
	{ "_PC_PRIO_IO",		_PC_PRIO_IO		},
#endif
#ifdef _PC_SYNC_IO
	{ "_PC_SYNC_IO",		_PC_SYNC_IO		},
#endif
	{ NULL,				-1			}
};

int main(void)
{
	const struct pcentry *pce;
	long rv;

	for (pce = pctable; pce != NULL; pce++) {
		if (pce->pc_desc == NULL && pce->pc_name == -1)
			break;

		errno = 0;
		rv = pathconf(".", pce->pc_name);
		printf("desc: %-20s\tvalue: %-10ld", pce->pc_desc, rv);
		if (rv == -1) {
			if (errno == 0)
				printf("\t[NO LIMIT]");
			else
				printf("\t[INVALID: %s]", strerror(errno));
		} else {
			printf("\t+SUPPORTED+");
		}

		printf("\n");
	}

	return (EXIT_SUCCESS);
}
