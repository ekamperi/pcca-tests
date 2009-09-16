/* $OpenBSD: pthread_kill.c,v 1.4 2003/07/31 21:48:05 deraadt Exp $ */
/* PUBLIC DOMAIN Oct 2002 <marc@snafu.org> */

/*
 * Verify that pthread_kill does the right thing, i.e. the signal
 * is delivered to the correct thread and proper signal processing
 * is performed.
 */

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void
act_handler(int signal, siginfo_t *siginfo, void *context)
{
	struct sigaction sa;

	assert(sigaction(SIGUSR1, NULL, &sa) != -1);
	assert(sa.sa_handler == SIG_DFL);
	assert(siginfo != NULL);
}
 
static void *
thread(void * arg)
{
	sigset_t run_mask;
	sigset_t suspender_mask;

	/*
	 * Run with all signals blocked.
	 *
	 * sigfillset() adds all signals to the list and
	 * sigprocmask() blocks the listed signals.
	 */
	sigfillset(&run_mask);
	assert(sigprocmask(SIG_SETMASK, &run_mask, NULL) != -1);

	/*
	 * sigsuspend() replaces the current signal mask and then suspends
	 * the thread until the delivery of a signal.
	 */
	sigfillset(&suspender_mask);
	sigdelset(&suspender_mask, SIGUSR1);

	/* Wait for SIGUSR1. */
	for (;;) {
		sigsuspend(&suspender_mask);
		assert(errno == EINTR);
	}		
}

int main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	struct sigaction act;

	/* Setup the signal handler. */
	act.sa_sigaction = act_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO | SA_RESETHAND | SA_NODEFER;

	/* Install the signal handler. */
	assert(sigaction(SIGUSR1, &act, NULL) != -1);

	/*
	 * Create the threads and sleep for a while, making sure that they are
	 * actually created (would a barrier be overkill here ?).
	 */
	assert(pthread_create(&thread1, NULL, thread, "T1") == 0);
	assert(pthread_create(&thread2, NULL, thread, "T2") == 0);
	sleep(1);

	/*
	 * Send us a SIGUSR1 signal.
	 * Signal handler should run once, both threads should awaken.
	 */
	assert(kill(getpid(), SIGUSR1) != -1);
	sleep(1);

	/* Signal handler sould run once, only T1 should awaken. */
	assert(sigaction(SIGUSR1, &act, NULL) != -1);
	assert(pthread_kill(thread1, SIGUSR1) == 0);
	sleep(1);

	/* Signal handler should run once, only T2 should awaken. */
	assert(sigaction(SIGUSR1, &act, NULL) != -1);
	assert(pthread_kill(thread2, SIGUSR1) == 0);
	sleep(1);

	printf("passed\n");
}
