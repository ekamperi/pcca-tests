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
	printf("%20s %10s %10s %8s %3s %4s %4s %4s\n",
	    "Name", "Ptr", "Mode", "Flags",  "Ref",
	    "MaxMsg", "MsgSze", "CurMsg");

	/* Get first mqueue (if any, otherwise NULL). */
	mq = LIST_FIRST(&mqueue_head);

	while (mq != NULL) {
		if (kvm_read(kd, (unsigned long)mq,
			&mq_data, sizeof(mq_data)) == sizeof(mq_data)) {
			printf("%20s %10p %10s %8x %3u %6lu %6lu %6lu\n",
			    mq_data.mq_name, mq, mode2str(mq_data.mq_mode),
			    mq_data.mq_attrib.mq_flags, mq_data.mq_refcnt,
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
