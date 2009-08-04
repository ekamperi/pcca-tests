sys/sem.h

_XOPEN_SOURCE 600 {
	#Semaphore operation flags:
	SEM_UNDO

	# Command definitions for the semctl() function.
	GETNCNT
	GETPID
	GETVAL
	GETALL
	GETZCNT
	SETVAL
	SETALL
}
