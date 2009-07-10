#include <assert.h>
#include <cpio.h>
#include <stdio.h>
#include <stdlib.h>

struct entry {
	int symbol;
	int value;
} table[] = {
	/*
	 * Undefined symbols will be caught by symgen.pl, so don't be
	 * too harsh here.
	 */
#ifdef	C_IRUSR
	{ C_IRUSR, 0000400 },
#endif
#ifdef	C_IWUSR
	{ C_IWUSR, 0000200 },
#endif
#ifdef	C_IXUSR
	{ C_IXUSR, 0000100 },
#endif
#ifdef	C_IRGRP
	{ C_IRGRP, 0000040 },
#endif
#ifdef	C_IWGRP
	{ C_IWGRP, 0000020 },
#endif
#ifdef	C_IXGRP
	{ C_IXGRP, 0000010 },
#endif
#ifdef	C_IROTH
	{ C_IROTH, 0000004 },
#endif
#ifdef	C_IWOTH
	{ C_IWOTH, 0000002 },
#endif
#ifdef	C_IXOTH
	{ C_IXOTH, 0000001 },
#endif
#ifdef	C_ISUID
	{ C_ISUID, 0004000 },
#endif
#ifdef	C_ISGID
	{ C_ISGID, 0002000 },
#endif
#ifdef	C_ISVTX
	{ C_ISVTX, 0001000 },
#endif
#ifdef	C_ISDIR
	{ C_ISDIR, 0040000 },
#endif
#ifdef	C_ISFIFO
	{ C_ISFIFO, 0010000 },
#endif
#ifdef	C_ISREG
	{ C_ISREG, 0100000 },
#endif
#ifdef	C_ISBLK
	{ C_ISBLK, 0060000 },
#endif
#ifdef	C_ISCHR
	{ C_ISCHR, 0020000 },
#endif
#ifdef	C_ISCTG
	{ C_ISCTG, 0110000 },
#endif
#ifdef	C_ISLNK
	{ C_ISLNK, 0120000 },
#endif
#ifdef	C_ISSOCK
	{ C_ISSOCK, 0140000 },
#endif
};


int main(void)
{
	size_t i, len;

	/* Get number of constants defined. */
	len = sizeof(table)/sizeof(table[0]);

	for (i = 0; i < len; i++)
	  assert(table[i].symbol == table[i].value);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
