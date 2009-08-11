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

#define _XOPEN_SOURCE 600

#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `semid_ds' structure must be defined, containing
	 * the following members.
	 */
	struct semid_ds sem;

	(void)sem.sem_perm;	/* Operation permission structure. */
	(void)sem.sem_nsems;	/* Number of semaphores in set. */
	(void)sem.sem_otime;	/* Last semop() time. */
	(void)sem.sem_ctime;	/* Last time changed by semctl(). */


	/*
	 * The `sembuf' structure must be defined, containing
	 * the following members.
	 */
	struct sembuf semb;

	(void)semb.sem_num;	/* Semaphore number. */
	(void)semb.sem_op;	/* Semaphore operation. */
	(void)semb.sem_flg;	/* Operation flags. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
