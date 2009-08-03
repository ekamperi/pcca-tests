#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `sigevent' structure must be defined, including at least
	 * the following members.
	 */
	struct sigevent sigev;

	(void)sigev.sigev_notify;	/* Notification type. */
	(void)sigev.sigev_signo;	/* Signal number. */
	(void)sigev.sigev_value;	/* Signal value. */
	(void)sigev.sigev_notify_function;	/* Notification function. */
	(void)sigev.sigev_notify_attributes;	/* Notification attributes. */

	/*
	 * The `sigaction' structure must be defined, including at least
	 * the following members.
	 */
	struct sigaction sa;

	(void)sa.sa_handler;	/* Pointer to a signal-catching function or
				   one of the macros SIG_IGN or SIG_DFL. */
	(void)sa.sa_mask;	/* Set of signals to be blocked during execution
				   of the signal handling function. */
	(void)sa.sa_flags;	/* Special flags. */
	(void)sa.sa_sigaction;	/* Pointer to a signal-catching function. */

	/*
	 * The `siginfo_t' type must be defined as structure, including at least
	 * the following members.
	 */
	siginfo_t si;

	(void)si.si_signo;	/* Signal number. */
	(void)si.si_code;	/* Signal code. */

	(void)si.si_errno;	/* If non-zero, an errno value associated with
				   this signal, as defined in <errno.h>. */
	(void)si.si_pid;	/* Sending process ID. */
	(void)si.si_uid;	/* Real user ID of sending process. */
	(void)si.si_addr;	/* Address of faulting instruction. */
	(void)si.si_status;	/* Exit value or signal. */
	(void)si.si_band;	/* Band event for SIGPOLL. */
	(void)si.si_value;	/* Signal value. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
