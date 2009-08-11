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
