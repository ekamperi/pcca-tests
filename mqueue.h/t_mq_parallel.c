#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	/* fork() */
#include <sys/wait.h>

#define LOGFILE		"logfile"
#define	MQNAME		"/abcde"
#define NMESSAGES	20000
#define MAXPRIO		100

mqd_t md;
int fd;

pthread_mutex_t mtx_aq;

/* Function prototypes. */
static void *thread1(void *arg);
static void *thread2(void *arg);

int main(void)
{
	pthread_t th1;
	pthread_t th2;
	mqd_t md;

	/* Initialize mutex. */
	assert(pthread_mutex_init(&mtx_aq, NULL) == 0);

	/* Create log file. */
        fd = open(LOGFILE, O_CREAT | O_TRUNC | O_WRONLY, 0777);
        assert(fd != -1);

	/* Create a message queue for read-write with default parameters. */
        md = mq_open(MQNAME, O_CREAT | O_EXCL | O_NONBLOCK | O_RDWR,
	    0700, NULL);
        assert (md != -1);

	/* Create threads. */
	assert(pthread_create(&th1, NULL, thread1, (void *)&md) == 0);
	assert(pthread_create(&th2, NULL, thread2, (void *)&md) == 0);

	/* Wait for threads to complete. */
	assert(pthread_join(th1, NULL) == 0);
	assert(pthread_join(th2, NULL) == 0);

	/* Destroy mutex. */
	assert(pthread_mutex_destroy(&mtx_aq) == 0);

	/* Close log file. */
	assert(close(fd) != -1);

	assert(mq_close(md) != -1);
	assert(mq_unlink(MQNAME) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread1(void *arg)
{
	char buf[100];
	mqd_t md;
	int i, rv;

	/* Retrieve argument. */
	md = *(mqd_t *)arg;

	/* Send messages with increasing priority. */
	for (i = 0; i < NMESSAGES; i++) {
		snprintf(buf, sizeof(buf), "parent: %d\n", i % MAXPRIO);

		pthread_mutex_lock(&mtx_aq);

		rv = mq_send(md, buf, sizeof(buf),
		    /* priority */ i % MAXPRIO);
		if (rv == -1 && errno == EAGAIN) {
			pthread_mutex_unlock(&mtx_aq);
			usleep(10);
			i--;
			continue;
		}
		assert(rv != -1);

		write(fd, buf, strlen(buf));

		pthread_mutex_unlock(&mtx_aq);
	}

	pthread_exit(NULL);
}

static void *
thread2(void *arg)
{
	char msg_recvd[8192];   /* Implementation defined. */
	char buf[100];
	unsigned int prio;
        mqd_t md;
	int i, rv;

        /* Retrieve argument. */
        md = *(mqd_t *)arg;

	for (i = 0; i < NMESSAGES; i++) {
		pthread_mutex_lock(&mtx_aq);

		rv = mq_receive(md, msg_recvd, sizeof(msg_recvd),
		    &prio);
		if (rv == -1 && errno == EAGAIN) {
			pthread_mutex_unlock(&mtx_aq);
			usleep(10);
			i--;
			continue;
		}
		assert(rv != -1);

		snprintf(buf, sizeof(buf), "child: %d\n", prio);
		write(fd, buf, strlen(buf));

		pthread_mutex_unlock(&mtx_aq);
	}

	pthread_exit(NULL);
}
