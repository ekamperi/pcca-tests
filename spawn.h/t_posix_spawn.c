#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <unistd.h>
#include <sys/wait.h>

int 
main(void)
{
	pid_t pid;
	char *argv[] = { "/bin/true", NULL, NULL, NULL };
	char *envp[] = {NULL};
  
	assert(posix_spawn(&pid, argv[0], /* actions */ NULL, /* attrs */ NULL,
		argv, envp) == 0);
	
	/* Wait for child to complete */
	int status;
	assert(wait(&status) == pid);
	assert(WIFEXITED(status));
	assert(WEXITSTATUS(status) == 0);

	printf("passed\n");
	
	return (EXIT_SUCCESS);
}
