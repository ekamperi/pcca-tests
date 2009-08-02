/*
 * Copyright (c) 2009, Stathis Kamperis
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define _XOPEN_SOURCE 600

#include <assert.h>
#include <fcntl.h>
#include <ndbm.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DBNAME	"t_ndbm.db"

#define NRECS	1024	/* Number of records. */
#define RECSIZE 128	/* Size of a record. */

/* Function prototypes. */
static void myhandler(int sig);

int main(void)
{
	char buf[NRECS][RECSIZE];
	DBM *pdb;
	datum key, data;
	int i, j, cnt, ignored, rv;

	/* Install signal handler. */
	signal(SIGABRT, myhandler);

	/* Initialize random number generator. */
	srand(time(NULL));

	/* Generate some random strings. */
	for (i = 0; i < NRECS; i++) {
		/* Zero out buffer. */
		memset(buf[i], 0, RECSIZE);
		for (j = 0; j < 1 + rand() % (RECSIZE-1); j++) {
			buf[i][j] = 'a' + rand() % ('z' - 'a');
		}
		/* printf("%s\n", buf[i]); */
	}

	/* Open the database. */
	pdb = dbm_open(DBNAME, O_RDWR | O_CREAT, 0777);
	assert(pdb != (DBM *)0);

	/* Feed them to database. */
	dbm_clearerr(pdb);	/* Sanity check. */

	ignored = 0;
	for (i = 0; i < NRECS; i++) {
		key.dptr = buf[i];
		key.dsize = sizeof(buf[i]);

		data.dptr = buf[i];
		data.dsize = sizeof(buf[i]);

		/*
		 * If the database already contains a record that matches the
		 * key arg, and store mode is set to DBM_INSERT, the existing
		 * record will be kept and the new record ignored.
		 * Also, `1' will be returned from dbm_store(), or `0' otherwise.
		 * Upon failure a negative value will be returned.
		 */
		rv = dbm_store(pdb, key, data, DBM_INSERT);
		assert(rv == 0 || rv == 1);
		assert(dbm_error(pdb) == 0);

		ignored += rv;
	}

	/* Iterate over the database. */
	cnt = 0;
	for (key = dbm_firstkey(pdb); key.dptr != NULL;
	     key = dbm_nextkey(pdb)) {
		cnt++;
	}

	/* Make sure that the numbers sum up. */
	assert(cnt + ignored == NRECS);

	/* XXX: Verify the integrity of the (key, data) pairs. */

	/* Close the database. */
	dbm_close(pdb);

	/*
	 * POSIX says that the database is stored in two files. One file is a
	 * directory containing a bitmap of keys and has .dir as its suffix.
	 * The second file contains all data and has .pag as its suffix.
	 * We are a bit lenient here and allow for different layout. That's
	 * why don't check against the return value of unlink(2).
	 */
	unlink("t_ndbm.db.db");
	unlink("t_ndbm.db.dir");
	unlink("t_ndbm.db.pag");

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void
myhandler(int sig)
{
	unlink("t_ndbm.db.db");
	unlink("t_ndbm.db.dir");
	unlink("t_ndbm.db.pag");
}
