/*
 * Copyright (c) 2009, Stathis Kamperis
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <assert.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mtx;
pthread_cond_t cond;

int hiprio = 0;
int lowprio = 0;
int hi_unblocked  = 0;	/* Whether the high priority thread was unblocked */
int low_unblocked = 0;	/* Whether the low priority thread was unblocked */

/* Function prototypes. */
static void *hiprio_thread(void *arg);
static void *lowprio_thread(void *arg);

int
main(void)
{
	struct sched_param param;

	/*
	 * Make sure that the setuid bit is set, the owner of the binary is root
	 * and that we were able to escalate our uid. This is a prerequisite.
	 */
	if (geteuid() != 0 ) {
		fprintf(stderr, "WARNING: We were unable to escalate our uid!\n"
		    "WARNING: Make sure that the binary has the setuid bit "
			"set, the owner is root and fs isn't mounted with some "
			"sort of nosuid option set.\n");
		assert(geteuid() == 0);
	}

	/* Initialize mutex lock and condition variable. */
	assert(pthread_mutex_init(&mtx, NULL) == 0);
	assert(pthread_cond_init(&cond, NULL) == 0);

	/* Get min, max priorities. */
	lowprio = sched_get_priority_min(SCHED_RR);
	hiprio = sched_get_priority_max(SCHED_RR);

	assert(lowprio != -1);
	assert(hiprio != -1);
	assert(lowprio < hiprio);

	/* Create a low priority thread. */
	pthread_attr_t lowprio_attr;
	pthread_t lowprio_tid;

	assert(pthread_attr_init(&lowprio_attr) == 0);
	assert(pthread_attr_setinheritsched(&lowprio_attr,
		PTHREAD_EXPLICIT_SCHED) == 0);
	assert(pthread_attr_setschedpolicy(&lowprio_attr, SCHED_RR) == 0);
	param.sched_priority = lowprio;
	assert(pthread_attr_setschedparam(&lowprio_attr, &param) == 0);
	assert(pthread_create(&lowprio_tid, &lowprio_attr, lowprio_thread, NULL)
	       == 0);

	/*
	 * Sleep a bit so that the low priority thread manages to acquire the
	 * mutex and block on the condition variable.
	 *
	 * We want the low thread to acquire _first_ the lock, in order to make
	 * sure that the lock order isn't more significant than the scheduling
	 * policy/priority.
	 */
	sleep(1);

	/* Create a high priority thread. */
	pthread_attr_t hiprio_attr;
	pthread_t hiprio_tid;

	assert(pthread_attr_init(&hiprio_attr) == 0);
	assert(pthread_attr_setinheritsched(&hiprio_attr,
		PTHREAD_EXPLICIT_SCHED) == 0);
	assert(pthread_attr_setschedpolicy(&hiprio_attr, SCHED_RR) == 0);
	param.sched_priority = hiprio;
	assert(pthread_attr_setschedparam(&hiprio_attr, &param) == 0);
	assert(pthread_create(&hiprio_tid, &hiprio_attr, hiprio_thread, NULL)
	    == 0);

	/*
	 * Sleep a bit so that the high priority thread manages to acquire the
	 * mutex and block on the condition variable.
	 */
	sleep(1);

	/*
	 * According to POSIX, all the threads that are unblocked by
	 * pthread_cond_broadcast() shall contend for the mutex according to the
	 * scheduling policy (if applicable), and as if each had called
	 * pthread_mutex_lock(). Here, we want to investigate whether the high
	 * priority thread takes precedence over the lower one.
	 *
	 * XXX: Concerns have been raised whether this test returns meaningful
	 * results. Some people suggested binding the two threads in the same
	 * CPU and using a more probalistic approach, such as making the threads
	 * busy-loop and see how far they have ran based on their priorities.
	 */
	assert(pthread_cond_broadcast(&cond) == 0);

	/* Wait for threads to complete. */
	assert(pthread_join(hiprio_tid, NULL) == 0);
	assert(pthread_join(lowprio_tid, NULL) == 0);

	/* Cleanup mutex and condition variable. */
	assert(pthread_mutex_destroy(&mtx) == 0);
	assert(pthread_cond_destroy(&cond) == 0);

	/* All the hassle was about this. */
	assert(hi_unblocked == 1);

	printf("passed\n");

	return (EXIT_SUCCESS);

}

static void *
hiprio_thread(void *arg)
{
	/*
	 * Just a sanity check.
	 *
	 * Make sure that the scheduling policy and scheduling priority are
	 * both correctly set.
	 */
	struct sched_param param;
	int policy;

	assert(pthread_getschedparam(pthread_self(), &policy, &param) == 0);
	assert(policy == SCHED_RR);
	assert(param.sched_priority == hiprio);

	/*
	 * Acquire the mutex.
	 *
	 * IMPORTANT: At this point the call to pthread_cond_wait() in low
	 * priority thread will have released the mutex lock. So, we can
	 * acquire it here, without being blocked!
	 */
	assert(pthread_mutex_lock(&mtx) == 0);

	/* This will block us! */
	assert(pthread_cond_wait(&cond, &mtx) == 0);

	/*
	 * Mark us as unblocked if and only if the low priority hasn't unblocked
	 * before us!
	 */
	if (low_unblocked == 0)
		hi_unblocked = 1;

	/* Release the mutex. */
	assert(pthread_mutex_unlock(&mtx) == 0);

	pthread_exit(NULL);
}

static void *
lowprio_thread(void *arg)
{
	/*
	 * Just a sanity check.
	 *
	 * Make sure that the scheduling policy and scheduling priority are
	 * both correctly set.
	 */
	struct sched_param param;
	int policy;

	assert(pthread_getschedparam(pthread_self(), &policy, &param) == 0);
	assert(policy == SCHED_RR);
	assert(param.sched_priority == lowprio);

	/* Acquire the mutex. */
	assert(pthread_mutex_lock(&mtx) == 0);

	/*
	 * This will block us!
	 *
	 * IMPORTANT: pthread_cond_wait() will automatically release the mutex
	 * that we pass to it, while it waits. Therefore, the mutex will become
	 * available for the high priority thread to acquire it.
	 */
	assert(pthread_cond_wait(&cond, &mtx) == 0);

	low_unblocked = 1;

	/* Release the mutex. */
	assert(pthread_mutex_unlock(&mtx) == 0);

	pthread_exit(NULL);
}
