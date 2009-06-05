#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define	TFILE	"tfile"

/* Function prototypes. */
static void diep(const char *);

int main(int argc, char *argv[])
{
	FILE *fp;
	pid_t pid;

	/* Check argument count. */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s /path/to/dir\n",
		    basename(argv[0]));
		exit(EXIT_FAILURE);
	}

	/* Change to target directory. */
	if (chdir(argv[1]) == -1)
		diep("chdir");

	/* Open tfile which has the name of the tests to execute. */
	fp = fopen(TFILE, "r");
	if (fp == NULL) {
		if (errno == ENOENT)
			exit(EXIT_FAILURE);

		printf("WEASDASDAS");
		diep("fopen");
	}

	/* Loop over the tfile. */
	char line[1024];
	while (!feof(fp)) {
		if (fgets(line, sizeof(line), fp) == NULL) {
			if (!feof(fp))
				diep("fgets");
		} else {
			/* Remove the trailing \n, if any. */
			line[strlen(line)-1] = '\0';

			/* Fork! */
			pid = fork();
			if (pid == -1)
				diep("fork");

			if (pid == 0) {
				/* We are inside the child. */
				struct stat sb;

				printf("%s: ", line);
				fflush(NULL);

				/* Does the test case actually exist ? */
				if (stat(line, &sb) == -1) {
					printf("failed (test doesn't exist)\n");
					fflush(NULL);
					exit(EXIT_FAILURE);
				}

				/* This should never return. */
				if (execl(line, line, (char *)0) == -1)
					diep("execl");
			} else {
				/* We are inside the parent. */
				int status;
				wait(&status);
			}
		}
	}

	if (pid != 0) {
		/* We are inside the parent -- cleanup. */
		fclose(fp);
	}

	return (EXIT_SUCCESS);
}

static void
diep(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
