/* $OpenBSD: pthread_kill.c,v 1.4 2003/07/31 21:48:05 deraadt Exp $ */
/* PUBLIC DOMAIN Oct 2002 <marc@snafu.org> */

/*
 * Verify that pthread_kill does the right thing, i.e. the signal
 * is delivered to the correct thread and proper signal processing
 * is performed.
 */

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int awake[2] = { 0 };
int sig_cnt = 0;

static void
myhandler(int sig, siginfo_t *siginfo, void *context)
{
	struct sigaction sa;

	sig_cnt++;

	assert(sigaction(SIGUSR1, NULL, &sa) != -1);
	assert(sa.sa_handler == SIG_DFL);
	assert(siginfo != NULL);
}
 
static void *
thread(void *arg)
{
	int id;
	sigset_t run_mask;
	sigset_t suspender_mask;

	/* Which thread are we ? */
	id = *(int *)arg;

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
	 * the thread until the delivery of a signal. There isn't really
	 * any success value for it. If it returns, it means that it was
	 * interrupted.
	 */
	sigfillset(&suspender_mask);
	sigdelset(&suspender_mask, SIGUSR1);

	/* Wait for SIGUSR1. */
	for (;;) {
		assert(sigsuspend(&suspender_mask) == -1);
		assert(errno == EINTR);
		awake[id]++;
	}

	pthread_exit(NULL);
}

int main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	struct sigaction sa;
	int id[2];

	/* Setup the signal handler. */
	sa.sa_sigaction = myhandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESETHAND | SA_NODEFER;

	/* Install the signal handler. */
	assert(sigaction(SIGUSR1, &sa, NULL) != -1);

	/*
	 * Create the threads and sleep for a while, making sure that they are
	 * actually created (would a barrier be overkill here ?).
	 */
	id[0] = 0;
	id[1] = 1;
	assert(pthread_create(&thread1, NULL, thread, &id[0]) == 0);
	assert(pthread_create(&thread2, NULL, thread, &id[1]) == 0);
	sleep(1);

	/*
	 * Send us (the process) a SIGUSR1 signal.
	 * It is indeterminate to which thread (main, thread 1, thread 2) will
	 * the signal be delivered.
	 */
	assert(kill(getpid(), SIGUSR1) != -1);
	sleep(1);
	assert(sig_cnt == 1);

	/* */
	awake[0] = 0;
	awake[1] = 0;

	/* Signal handler sould run once, only tread 1 should awaken. */
	assert(sigaction(SIGUSR1, &sa, NULL) != -1);
	assert(pthread_kill(thread1, SIGUSR1) == 0);
	sleep(1);
	assert(sig_cnt == 2 && awake[0] == 1 && awake[1] == 0);

	/* Signal handler should run once, only thread 2 should awaken. */
	assert(sigaction(SIGUSR1, &sa, NULL) != -1);
	assert(pthread_kill(thread2, SIGUSR1) == 0);
	sleep(1);
	assert(sig_cnt == 3 && awake[1] == 1 && awake[1] == 1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
