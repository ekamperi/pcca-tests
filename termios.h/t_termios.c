#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

int main(void)
{
	struct termios t;

	/* The termios structure needs the following members: */
	(void)t.c_iflag;	/* Input modes. */
	(void)t.c_oflag;	/* Output modes. */
	(void)t.c_cflag;	/* Control modes. */
	(void)t.c_lflag;	/* Local modes. */
	(void)t.c_cc;		/* Control characters. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
