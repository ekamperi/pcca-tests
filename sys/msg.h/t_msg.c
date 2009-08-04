//#define _XOPEN_SOURCE 600

#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `msqid_ds' structure must be defined, including the
	 * following members.
	 */
	struct msqid_ds msg;

	(void)msg.msg_perm;	/* Operation permission structure. */
	(void)msg.msg_qnum;	/* Number of messages currently on queue. */
	(void)msg.msg_qbytes;	/* Maximum number of bytes allowed on queue. */
	(void)msg.msg_lspid;	/* Process ID of last msgsnd(). */
	(void)msg.msg_lrpid;	/* Process ID of last msgrcv(). */
	(void)msg.msg_stime;	/* Time of last msgsnd(). */
	(void)msg.msg_rtime;	/* Time of last msgrcv(). */
	(void)msg.msg_ctime;	/* Time of last change. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
