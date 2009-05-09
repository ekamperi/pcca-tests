#include <assert.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* fork() */

#define	MQNAME	"/mqueue1"

static void diep(const char *s);

int main(void)
{
	const char *msg = "Parent says hello";
	int rv;
	mqd_t md;
	pid_t pid;

	/* create a message queue for write only with default perms */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0777, NULL);
	if (md == -1)
		diep("mq_open");

	/* send message */
	rv = mq_send(md, msg, sizeof(msg), /* priority */ 0);
	if (rv == -1)
		diep("mq_send");

	/* disassociate with message queue */
	rv = mq_close(md);
	if (rv == -1)
		diep("mq_close");

	/* fork and have child read the message from parent */
	pid = fork();
	if (pid == -1) {
		diep("fork");
	} else if (pid == 0) {
		/* we are inside the child */
		md = mq_open(MQNAME, O_RDONLY);
		if (md == -1)
			diep("child: mq_open");

		char msg_recvd[10000];
		rv = mq_receive(md, msg_recvd, sizeof(msg_recvd), NULL);
		if (rv == -1) 
			diep("child: mq_receive");

		printf("child received message: %s\n", msg);

		/* disassociate with message queue */
		rv = mq_close(md);
		if (rv == -1)
			diep("child: mq_close");

		/* remove the message queue */
		rv = mq_unlink(MQNAME);
		if (rv == -1)
			diep("mq_unlink");
	} else {
		/* we are inside the parent */
		
	}

  return EXIT_SUCCESS;
}

void diep(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
