#include <assert.h>
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

/* Function prototypes. */
static void myhandler(int sig);

int main(void)
{
	char buf[100];
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
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDWR, 0700, NULL);
	assert (md != -1);

	/* Fork and let the game begin. */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */
	  printf("parent = %d\n", getpid());


		for (i = 0; i < NMESSAGES; i++) {

			snprintf(buf, sizeof(buf), "%d", i % MAXPRIO);

                        /* Send messages with increasing priority. */
                        rv = mq_send(md, buf, sizeof(buf),
                            /* priority */ i % MAXPRIO);
                        assert(rv != -1);

			snprintf(buf, sizeof(buf), "p: %d\n", i % MAXPRIO);
			//assert(lockf(fd, F_LOCK, 0) != -1);
			if (lockf(fd, F_LOCK, (off_t)0) == -1) {
				perror("lockf parent: ");
				assert(0);
			}
			write(fd, buf, strlen(buf));
			assert(lockf(fd, F_ULOCK, (off_t)0) != -1);
		}

		assert(close(fd) != -1);

		/* Disassociate with message queue. */
		rv = mq_close(md);
		assert(rv != -1);

		/* Wait until child has read all messages. */
		int status;
		wait(&status);

                /* Remove the message queue from the system. */
                /*rv = mq_unlink(MQNAME);
		perror("mq_unlink");
                assert(rv != -1);*/

                printf("passed\n");
	} else {
	  printf("child = %d\n", getpid());
		/* We are inside the child. */
		char msg_recvd[8192];   /* Implementation defined. */
		unsigned int oldprio = UINT_MAX, prio, priostr;

		for (i = 0; i < NMESSAGES; i++) {
			rv = mq_receive(md, msg_recvd, sizeof(msg_recvd),
			    &prio);
			assert(rv != -1);

			snprintf(buf, sizeof(buf), "c: %s\n", msg_recvd);
			assert(lockf(fd, F_LOCK, (off_t)0) != -1);
			write(fd, buf, strlen(buf));
			assert(lockf(fd, F_ULOCK, (off_t)0) != -1);

			//printf("msg = %s\n", msg_recvd);
			//fflush(NULL);

			priostr = atoi(msg_recvd);
			//printf("%d\n", priostr);
			assert(priostr == prio);

			//printf("prio = %d\toldprio = %d\n", prio, oldprio);
			//assert(prio < oldprio);
			oldprio = prio;

			//printf("prio = %d\tpriostr = %d\toldprio = %d\n",
			//prio, priostr, oldprio);
		}

	}

	return EXIT_SUCCESS;
}

static void
myhandler(int sig)
{
	/*
	 * Message queues' name & resources are persistent, i.e., they live
	 * even after the process dies. That's why, disassociate and destroy
	 * the queue on failure, or else we might end up with zombie queues and
	 * hit the limit of max open queues.
	 * Also, we don't care about the return value of the following calls.
	 */
	mq_close(md);
	mq_unlink(MQNAME);

	/* After this, the program will abort. */
}
