#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*
 * Missing baud rates symbols will be caught by symgen.pl,
 * so be a bit lenient here.
 */
speed_t speeds[] = {
#ifdef B0
	B0,
#endif
#ifdef B50
	B50,
#endif
#ifdef B75
	B75,
#endif
#ifdef B110
	B110,
#endif
#ifdef B134
	B134,
#endif
#ifdef B150
	B150,
#endif
#ifdef B200
	B200,
#endif
#ifdef B300
	B300,
#endif
#ifdef B600
	B600,
#endif
#ifdef B1200
	B1200,
#endif
#ifdef B1800
	B1800,
#endif
#ifdef B2400
	B2400,
#endif
#ifdef B4800
	B4800,
#endif
#ifdef B9600
	B9600,
#endif
#ifdef B19200
	B19200,
#endif
#ifdef B38400
	B38400
#endif
};

int main(void)
{
	struct termios t;
	speed_t ns, s;
	size_t i, speedfound;

	/* Make sure we are associated with a tty. */
	assert(isatty(STDIN_FILENO) != 0);

	/* Get current termios structure. */
	assert(tcgetattr(STDIN_FILENO, &t) != -1);

	/*
	 * Extract speed.
	 * XXX: Can conformant implementations provide a speed beyond B38400 ?
	 */
	s = cfgetispeed(&t);

	speedfound = 0;
	for (i = 0; i < sizeof(speeds) / sizeof(speeds[0]); i++) {
		if (s == speeds[i]) {
			speedfound = 1;
			break;
		}
	}

	assert(speedfound == 1);

	/*
	 * Set new speed.
	 * But first make sure that we don't set the speed to the old value.
	 */
	ns = s;
	for (i = 0; i < sizeof(speeds) / sizeof(speeds[0]); i++) {
		if (speeds[i] != s) {
			ns = speeds[i];
			break;
		}
	}

	/*
	 * A bit paranoid, since this assertion would fail only if there was
	 * just one baud rate available.
	 */
	assert(ns != s);
	cfsetispeed(&t, ns);

	/* Make sure the new speed was actually set. */
	s = cfgetispeed(&t);
	assert(s == ns);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
