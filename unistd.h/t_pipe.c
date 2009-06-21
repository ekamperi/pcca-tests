#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	char buf[1024];
	int fd[2], status;
	pid_t pid;

	/*
	 * Create pipe (fd[0] is the read end, fd[1] is the write end).
	 * File descriptors are inherited by child upon fork, and point
	 to the same underlying objects.
	*/
	assert(pipe(fd) != -1);

	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */
		assert(close(fd[0]) != -1);
		assert(write(fd[1], "Parent says hello\n", 19) == 19);

		/* Wait for child to complete. */
		wait(&status);

		printf("passed\n");
		
	} else {
		/* We are inside the child. */
		assert(close(fd[1]) != -1);
		assert(read(fd[0], buf, sizeof(buf)) == 19);
	}

	return (EXIT_SUCCESS);
}
