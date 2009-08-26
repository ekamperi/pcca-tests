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
#include <unistd.h>
#include <stdlib.h>

static void
act_handler(int signal, siginfo_t *siginfo, void *context)
{
	struct sigaction sa;
	char *str;

	assert(sigaction(SIGUSR1, NULL, &sa) != -1);
	assert(sa.sa_handler == SIG_DFL);
	assert(siginfo != NULL);
#if 
	asprintf(&str, "act_handler: signal %d, siginfo %p, context %p\n",
		 signal, siginfo, context);
	write(STDOUT_FILENO, str, strlen(str));
	free(str);
}
 
static void *
thread(void * arg)
{
	sigset_t run_mask;
	sigset_t suspender_mask;

	/* wait for sigusr1 */

	/* Run with all signals blocked, then suspend for SIGUSR1 */
	sigfillset(&run_mask);
	assert(sigprocmask(SIG_SETMASK, &run_mask, NULL) != -1);
	sigfillset(&suspender_mask);
	sigdelset(&suspender_mask, SIGUSR1);
	for (;;) {
		sigsuspend(&suspender_mask);
		assert(errno == EINTR);
		printf("Thread %s woke up\n", (char*) arg);
	}
		
}

int main(int argc, char **argv)
{
	pthread_t thread1;
	pthread_t thread2;
	struct sigaction act;

	act.sa_sigaction = act_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO | SA_RESETHAND | SA_NODEFER;
	assert(sigaction(SIGUSR1, &act, NULL) != -1);
	assert(pthread_create(&thread1, NULL, thread, "T1") == 0);
	assert(pthread_create(&thread2, NULL, thread, "T2") == 0);
	sleep(1);

	/* Signal handler should run once, both threads should awaken */
	assert(kill(getpid(), SIGUSR1) != -1);
	sleep(1);

	/* Signal handler run once, only T1 should awaken */
	assert(sigaction(SIGUSR1, &act, NULL) != -1);
	assert(pthread_kill(thread1, SIGUSR1) == 0);
	sleep(1);

	/* Signal handler run once, only T2 should awaken */
	assert(sigaction(SIGUSR1, &act, NULL) != -1);
	assert(pthread_kill(thread2, SIGUSR1) == 0);
	sleep(1);

	printf("passed\n");
}