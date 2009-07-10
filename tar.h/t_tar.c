#define	_XOPEN_SOURCE	600	/* for TSVTX */

#include <assert.h>
#include <cpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct entry {
	int symbol;
	int value;
};

/* General constants. */
struct entry gtable[] = {
#ifdef	TMAGLEN
	{ TMAGLEN, 6 },
#endif
#ifdef	TVERSLEN
	{ TVERSLEN, 2 }
#endif
};

/* Type flag constants. */
struct entry tftable[] = {
	/*
	 * Undefined symbols will be caught by symgen.pl, so don't be
	 * too harsh here.
	 */
#ifdef	REGTYPE
	{ REGTYPE, '0' },
#endif
#ifdef	AREGTYPE
	{ AREGTYPE, '\0' },
#endif
#ifdef	LNKTYPE
	{ LNKTYPE, '1' },
#endif
#ifdef	SYMTYPE
	{ SYMTYPE, '2' },
#endif
#ifdef	CHRTYPE
	{ CHRTYPE, '3' },
#endif
#ifdef	BLKTYPE
	{ BLKTYPE, '4' },
#endif
#ifdef	DIRTYPE
	{ DIRTYPE, '5' },
#endif
#ifdef	FIFOTYPE
	{ FIFOTYPE, '6' },
#endif
#ifdef	CONTTYPE
	{ CONTTYPE, '7' },
#endif
};

struct entry mftable[] = {
#ifdef	TSUID
	{ TSUID, 0000400 },
#endif
#ifdef	TSGID
	{ TSGID, 0000200 },
#endif
#ifdef	TSVTX
	{ TSVTX, 0000100 },
#endif
#ifdef	TUREAD
	{ TUREAD, 0000040 },
#endif
#ifdef	TUWRITE
	{ TUWRITE, 0000020 },
#endif
#ifdef	TUEXEC
	{ TUEXEC, 0000010 },
#endif
#ifdef	TGREAD
	{ TGREAD, 0000004 },
#endif
#ifdef	TGWRITE
	{ TGWRITE, 0000002 },
#endif
#ifdef	TGEXEC
	{ TGEXEC, 0000001 },
#endif
#ifdef	TOREAD
	{ TOREAD, 0000004 },
#endif
#ifdef	TOWRITE
	{ TOWRITE, 0000002 },
#endif
#ifdef	TOEXEC
	{ TOEXEC, 0000001 },
#endif
};

int main(void)
{
	size_t i, len;

	/* Get number of general constants defined. */
	len = sizeof(gtable)/sizeof(gtable[0]);
	for (i = 0; i < len; i++)
		assert(gtable[i].symbol == gtable[i].value);

#ifdef	TMAGIC
	assert(strcmp(TMAGIC, "ustar") == 0);
#endif
#ifdef	TVERSION
	assert(strcmp(TVERSION, "00") == 0);
#endif

	/* Get number of typeflag constants defined. */
	len = sizeof(tftable)/sizeof(tftable[0]);
	for (i = 0; i < len; i++)
		assert(tftable[i].symbol == tftable[i].value);

	/* Get number of mode field constants defined. */
	len = sizeof(mftable)/sizeof(mftable[0]);
	for (i = 0; i < len; i++)
		assert(mftable[i].symbol == mftable[i].value);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
