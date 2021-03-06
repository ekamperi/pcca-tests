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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <kvm.h>

#define _KERNEL_STRUCTURES
#include <sys/mqueue.h>

static LIST_HEAD(, mqueue) mqueue_head =
		LIST_HEAD_INITIALIZER(mqueue_head);

static kvm_t *kd;

/*
 * We need an array of nlist symbols, that
 * terminates with a NULL n_name field.
 */
static struct nlist symbols[] = {
	{ "_mqueue_head" },
	{ NULL }
};

/* Function prototypes. */
static char *mode2str(mode_t mode);
static char *attr2str(struct mq_attr attr);

int main(void)
{
	char *execfile = NULL;	/* kernel executable image */
	char *corefile = NULL;	/* kernel memory device file */
	char *swapfile = NULL;	/* swap device */

	/*
	 * Get a descriptor to access kernel virtual memory via the kvm(3)
	 * library routines. By passing NULL to the following arguments,
	 * we imply the default values (respectively).
	 */
	kd = kvm_open(execfile, corefile, swapfile, O_RDONLY, "kvm_open");
	if (kd == NULL)
		exit(EXIT_FAILURE);

	/* Retrieve symbol table entries. */
	if (kvm_nlist(kd, symbols) == -1) {
		fprintf(stderr, "kvm_nlist: %s\n", kvm_geterr(kd));
		exit(EXIT_FAILURE);
	}

	/* XXX: Proper error handling. */
	assert(symbols[0].n_value != 0);

	/* Read the head of the list with the message queues. */
	if (kvm_read(kd, symbols[0].n_value, &mqueue_head, sizeof(mqueue_head))
	    != sizeof(mqueue_head)) {
		fprintf(stderr, "kvm_read: %s\n", kvm_geterr(kd));
		exit(EXIT_FAILURE);
	}

	/*
	 * Enumerate active POSIX message queues.
	 *
	 * SysV message queues are listed via ipcs(1), along with the rest of
	 * the SysV interprocess communication facilities.
	 */
	struct mqueue mq_data;
	struct mqueue *mq;

	printf("Global list of the message queues:\n");
	printf("%20s %10s %10s %10s %3s %4s %4s %4s\n",
	    "Name", "Ptr", "Mode", "Flags",  "Ref",
	    "MaxMsg", "MsgSze", "CurMsg");

	/* Get first mqueue (if any, otherwise NULL). */
	mq = LIST_FIRST(&mqueue_head);

	while (mq != NULL) {
		if (kvm_read(kd, (unsigned long)mq,
			&mq_data, sizeof(mq_data)) == sizeof(mq_data)) {
			printf("%20s %10p %10s %10s %3u %6lu %6lu %6lu\n",
			    mq_data.mq_name, mq, mode2str(mq_data.mq_mode),
			    attr2str(mq_data.mq_attrib), mq_data.mq_refcnt,
			    mq_data.mq_attrib.mq_maxmsg, mq_data.mq_attrib.mq_msgsize,
			    mq_data.mq_attrib.mq_curmsgs);
		} else {
			/*
			 * Be lenient and continue listing the rest of the
			 * queues. Although, there is really low probability that
			 * if one call kvm_call() fails, the rest will succeed.
			 */
			fprintf(stderr, "kvm_read: %s\n", kvm_geterr(kd));
		}
		mq = LIST_NEXT(&mq_data, mq_list);
	}

	/* We are done -- close kvm channel. */
	if (kvm_close(kd) == -1) {
		fprintf(stderr, "kvm_close: %s\n", kvm_geterr(kd));
		exit(EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

static char *mode2str(mode_t mode)
{
	static char str[10];

	/* owner */
	str[0] = (mode & S_IRUSR) ? 'r' : '-';
	str[1] = (mode & S_IWUSR) ? 'w' : '-';
	str[2] = (mode & S_IXUSR) ? 'x' : '-';

	/* group */
	str[3] = (mode & S_IRGRP) ? 'r' : '-';
	str[4] = (mode & S_IWGRP) ? 'w' : '-';
	str[5] = (mode & S_IXGRP) ? 'x' : '-';

	/* others */
	str[6] = (mode & S_IROTH) ? 'r' : '-';
	str[7] = (mode & S_IWOTH) ? 'w' : '-';
	str[8] = (mode & S_IXOTH) ? 'x' : '-';

	/* terminate string */
	str[9] = '\0';

	return (str);
}

static char *attr2str(struct mq_attr attr)
{
	static char str[5];

        if (attr.mq_flags & O_RDWR) {
		str[0] = 'R';
		str[1] = 'W';
        } else if (attr.mq_flags & O_RDONLY) {
		str[0] = 'R';
		str[1] = '-';
	} else if (attr.mq_flags & O_WRONLY) {
		str[0] = '-';
		str[1] = 'W';
	} else {
		str[0] = '?';
		str[1] = '?';
	}

	str[2] = (attr.mq_flags & O_NONBLOCK) ? '-' : 'B';
	str[3] = (attr.mq_flags & MQ_UNLINK ) ? 'U' : '-';

	/* terminate string */
	str[4] = '\0';

	return (str);
}
