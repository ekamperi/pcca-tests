#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	/* fork() */
#include <sys/wait.h>

#define LOGFILE		"logfile"
#define	MQNAME		"/tmqpcmp1"
#define NMESSAGES	10000
#define MAXPRIO		32

mqd_t md;

#define INITLOCK(lck)			\
	do {				\
		lck.l_type = F_WRLCK;	\
		lck.l_whence = 0;	\
		lck.l_start = 0L;	\
		lck.l_len = 0L;		\
	} while(0)

#define INITUNLOCK(lck)			\
        do {				\
		lck.l_type = F_UNLCK;	\
		lck.l_whence = 0;	\
		lck.l_start = 0L;	\
		lck.l_len = 0L;		\
        } while(0)

/* Function prototypes. */
static void myhandler(int sig);

int main(void)
{
	char buf[100];
	struct flock lck;
	size_t i;
	int fd, rv;
	pid_t pid;

	/*
	 * Create log file.
	 * The file must be created in O_WRONLY or O_RDWR mode,
	 * or else lockf(3) will be very very unhappy.
	 */
	fd = open(LOGFILE, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	assert(fd != -1);

	/* Install signal handler. */
	signal(SIGABRT, myhandler);

	/* Create a message queue for write only with default parameters. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_NONBLOCK | O_RDWR,
	    0777, NULL);
	assert (md != -1);

	/* Fork and let the game begin. */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */

		for (i = 0; i < NMESSAGES; i++) {

			snprintf(buf, sizeof(buf), "parent: %d\n", i % MAXPRIO);

			INITLOCK(lck);
			fcntl(fd, F_SETLKW, &lck);

                        /* Send messages with increasing priority. */
                        rv = mq_send(md, buf, sizeof(buf), i % MAXPRIO);
			if (rv == -1 && errno == EAGAIN) {
				INITUNLOCK(lck);
				assert(fcntl(fd, F_SETLKW, &lck) != -1);
				usleep(10);
				i--;
				continue;
			}
                        assert(rv != -1);

			write(fd, buf, strlen(buf));

			INITUNLOCK(lck);
			assert(fcntl(fd, F_SETLKW, &lck) != -1);
		}

		/* Wait until child has read all messages. */
		int status;
		wait(&status);

		assert(close(fd) != -1);

		/* Disassociate with message queue. */
                rv = mq_close(md);
                assert(rv != -1);

                /* Remove the message queue from the system. */
                rv = mq_unlink(MQNAME);
                assert(rv != -1);

                printf("passed\n");
	} else {
		/* We are inside the child. */
		char msg_recvd[8192];   /* Implementation defined. */
		unsigned int oldprio = UINT_MAX, prio, priostr;

		for (i = 0; i < NMESSAGES; i++) {
			INITLOCK(lck);
			fcntl(fd, F_SETLKW, &lck);

			rv = mq_receive(md, msg_recvd, sizeof(msg_recvd),
			    &prio);
			if (rv == -1 && errno == EAGAIN) {
				INITUNLOCK(lck);
				assert(fcntl(fd, F_SETLKW, &lck) != -1);
				usleep(10);
				i--;
				continue;
			}
			assert(rv != -1);

			snprintf(buf, sizeof(buf), "child: %d\n", prio);
			write(fd, buf, strlen(buf));

			assert(fcntl(fd, F_SETLKW, &lck) != -1);
		}

	}

	return EXIT_SUCCESS;
}

static void
myhandler(int sig)
{
	mq_close(md);
	mq_unlink(MQNAME);
}
