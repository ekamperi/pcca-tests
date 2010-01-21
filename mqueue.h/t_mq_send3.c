#include <assert.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MQNAME    "/t_mq_send3"
#define NMESSAGES 10

/* Function prototypes. */
static void intrhandler(int signo);

int
main(void)
{
	/* Create message queue with maxmsg `10'. */
	struct mq_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = NMESSAGES;	/* Maximum number of messages. */
	attr.mq_msgsize = 1024;		/* Maximum message size. */

	/*
	 * We intentionally omit the O_NONBLOCK flag as we want our queue to
	 * operate on blocking mode.
	 */
	mqd_t md;

	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDWR, 700, &attr);
	assert(md != (mqd_t)-1);

	/*
	 * A little bit of paranoia.
	 * Make sure that the maximum number of messages is equal to what we
	 * set it. I.e., it didn't round up under our feet, which would defeat
	 * the whole purpose of the test.
	 */
	memset(&attr, 0, sizeof(attr));

	assert(mq_getattr(md, &attr) != -1);
	assert(attr.mq_maxmsg == NMESSAGES);

	pid_t pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */

		/*
		 * Send one more message than the maximum messages the queue
		 * can hold. In the last message, the mq_send() call will block.
		 */
		size_t i;

		for (i = 0; i < NMESSAGES + 1; i++) {
			assert(mq_send(md, "foo", sizeof("foo"),
				/* priority */ i + 1) != -1);
		}
	} else {
		/*
		 * We are inside the parent.
		 *
		 * Sleep a bit so that child takes its time to block on
		 * mq_send().
		 */
		assert(sleep(2) == 0);

		/*
		 * Start draining messages from the queue.
		 * Messages are sent with increasing priority, so the last sent
		 * is the first to be delivered.
		 */
		char buf[1024];
		int rv;
		unsigned int prio;

		/*
		 * 10th message --
		 * this means that the last mq_send() call blocked.
		 */
		assert(mq_receive(md, buf, sizeof(buf), &prio) != -1);
		assert(prio == NMESSAGES);

		assert(sleep(1) == 0);

		/*
		 * 11th message --
		 * this means that the last mq_send() call unblocked as it ought
		 * to.
		 */
		assert(mq_receive(md, buf, sizeof(buf), &prio) != -1);
		assert(prio == NMESSAGES + 1);

		/* We are done -- cleanup */
		assert(mq_close(md) != -1);
		assert(mq_unlink(MQNAME) != -1);

		printf("passed\n");

		return (EXIT_SUCCESS);
	}

	/* Only reached by the child. */
	return (EXIT_SUCCESS);
}
