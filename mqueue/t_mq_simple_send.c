#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void diep(const char *s);

int main(void)
{
	const char msg[] = "this is a test";
	mqd_t md;
	int rv;

	md = mq_open("/mq123", O_CREAT | O_EXCL | O_WRONLY, 0777, NULL);
	if (md == -1)
		diep("mq_open");

	rv = mq_send(md, msg, sizeof(msg), 0);
	if (rv == -1)
		diep("mq_send");

	rv = mq_close(md);
	if (rv == -1)
		diep("mq_close");

}

void diep(const char *s)
{
        perror(s);
        exit(EXIT_FAILURE);
}
