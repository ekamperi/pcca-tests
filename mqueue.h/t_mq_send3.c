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

#define MQNAME "/t_mq_send3"
#define NMESSAGES 5

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

	md = mq_open(MQNAME, O_CREAT | O_RDWR, 700, &attr);
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
		/* Sleep a bit so that parent manages to setup the handler. */
		assert(sleep(1) == 0);

		/*
		 * Send one more message than the maximum messages the queue
		 * can hold. In the last message, the mq_send() call will block.
		 */
		size_t i;
		for (i = 0; i < NMESSAGES + 1; i++) {
			assert(mq_send(md, "foo", sizeof("foo"),
				/* priority */ 0) != -1);

			/*
			 * Notify the parent that we have sent a message, by
			 * sending him a signal.
			 */
			assert(kill(getppid(), SIGUSR1) != -1);
		}
	} else {
		/* We are inside the parent. */
		/* Setup signal handler. */
		struct sigaction sa;

		sa.sa_handler = intrhandler;
		sa.sa_flags = 0;
		assert(sigemptyset(&sa.sa_mask) != -1);
		assert(sigaction(SIGUSR1, &sa, 0) != -1);

		size_t i;
		for (i = 0; i < NMESSAGES + 1; i++) {
			/*
			 * The value returned by sleep() is the `unslept'
			 * amount.
			 */
			if (sleep(2) == 0) {
				/*
				 * If sleep() completed, child is most likely
				 * being blocked on mq_send().
				 */
				break;
			}
		}

		/* If child never blocked, it's a failure. */
		assert(i < NMESSAGES);

		/*
		 * We receive a message from the queue.
		 * This should normally cause the child that is blocked on
		 * mq_send() to unblock and complete.
		 */
		char buf[1024];
		int rv;
		unsigned int prio;

		rv = mq_receive(md, buf, sizeof(buf), &prio);
		if (rv == -1) {
			/* Kill child. */
			assert(kill(pid, SIGKILL) != -1);

			/* Probe its status to make sure it's gone. */
			int status;
			assert(wait(&status) == pid);

			/* Abort. */
			assert(rv != -1);
		}

		/*
		 * At this point the child has been unblocked and sent us the
		 * last message along with the last SIGUSR1 signal.
		 */
		rv = sleep(3);
		if (rv == 0) {
			/* Kill child. */
			assert(kill(pid, SIGKILL) != -1);
			assert(rv != 0);
		}

		/* We are done -- cleanup */
		assert(mq_close(md) != -1);
		assert(mq_unlink(MQNAME) != -1);
		printf("passed\n");

		return (EXIT_SUCCESS);
	}

	/* Only reached by child. */
	return (EXIT_SUCCESS);
}

static void
intrhandler(int signo)
{
	/* To keep compiler happy. */
	(void)signo;

	return;
}
