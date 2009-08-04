#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

int main(void)
{
	struct shmid_ds s;

	/* POSIX mandates the following members. */
	(void)s.shm_perm;	/* Operation permission structure. */
	(void)s.shm_segsz;	/* Size of segment in bytes. */
	(void)s.shm_lpid;	/* ProcessID of last shared memory operation. */
	(void)s.shm_cpid;	/* ProcessID of creator. */
	(void)s.shm_nattch;	/* Number of current attaches. */
	(void)s.shm_atime;	/* Time of last shmat(). */
	(void)s.shm_dtime;	/* Time of last shmdt(). */
	(void)s.shm_ctime;	/* Time of last change by shmctl(). */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
