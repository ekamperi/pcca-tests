#include <assert.h>
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MQNAME	"/t_mq_open_umask"

int
main(void)
{
	/*
	 * Set the file creation mask to u=rwx g=rwx o=rwx.
	 *
	 * We will check later on, if it is honoured during the creation
	 * of a new message queue.
	 */
	umask(777);

	/*
	 * Create the message queue with permission bits set to 777.
	 *
	 * But since the file creation mask is already 777, the queue should be
	 * created with 000.
	 */
	mqd_t md;

	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDWR, 0777, NULL);
	assert(md != (mqd_t)-1);

        /* Disassociate from the message queue. */
        assert(mq_close(md) != -1);

	/* Fork! */
	pid_t pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */

		/*
		 * The file creation mask isn't inherited by the child process,
		 * during fork(). Given this info, we try to open the queue with
		 * inappropriate permission bits.
		 */
		mode_t modes[] = { 000,	001, 002, 004,	/* XXX: What about 000 ? */
				   010, 012, 011, 014,
				   020, 021, 022, 024,
				   040, 041, 042, 044,

				   100, 101, 102, 104,
				   110, 111, 112, 114,
				   120, 121, 122, 124,
				   140, 141, 142, 144,

				   200, 201, 202, 204,
				   210, 211, 212, 214,
				   220, 221, 222, 224,
				   240, 241, 242, 244,

				   400, 401, 402, 404,
				   410, 411, 412, 414,
				   420, 421, 422, 424,
				   440, 441, 442, 444

				   /*
				    * We expect or rather hope that the combined
				    * permission bits, e.g. 777, are covered by
				    * the above fundamental set.
				    */
		};

		size_t i;
		for (i = 0; i < sizeof(modes) / sizeof(*modes); i++)
			assert(mq_open(MQNAME, O_CREAT, modes[i]) == (mqd_t)-1
			    && errno == EACCES);

		/* Remove the message queue from the system. */
		assert(mq_unlink(MQNAME) != -1);

		printf("passed\n");

	} else {
		/* We are inside the parent. */

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		/*
		 * Determine if the child exited normally, or due to a SIGABRT
		 * signal being delivered to it by a failed assertion.
		 */
		if (WIFSIGNALED(status)) {
			assert(WTERMSIG(status) == SIGABRT);
			return (EXIT_FAILURE);
		} else {
			return (EXIT_SUCCESS);
		}
	}
}
