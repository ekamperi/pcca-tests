#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void diep(const char *s);

int main(void)
{
	char msg[8192];
	mqd_t md;
	int rv;

	md = mq_open("/tmqss", O_RDONLY);
	if (md == -1)
		diep("mq_open");

	rv = mq_receive(md, msg, sizeof(msg), NULL);
	if (rv == -1)
		diep("mq_receive");

	rv = mq_close(md);
	if (rv == -1)
		diep("mq_close");

	return (EXIT_SUCCESS);
}

void diep(const char *s)
{
        perror(s);
        exit(EXIT_FAILURE);
}
