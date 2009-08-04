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
