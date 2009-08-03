#include <stropts.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `bandinfo' structure must be defined, including at least
	 * the following members.
	 */
	struct bandinfo bi;
	(void)bi.bi_pri;	/* Priority band. */
	(void)bi.bi_flag;	/* Flushing type. */

	/*
	 * The `strpeek' structure must be defined, including at least
	 * the following members.
	 */
	struct strpeek sp;

	(void)sp.ctlbuf;	/* The control portion of the message. */
	(void)sp.databuf;	/* The data portion of the message. */
	(void)sp.flags;		/* RS_HIPRI or 0. */

	/*
	 * The `strbuf' structure must be defined, including at least
	 * the following members.
	 */
	struct strbuf sb;

	(void)sb.maxlen;	/* Maximum buffer length. */
	(void)sb.len;		/* Length of data. */
	(void)sb.buf;		/* Pointer to buffer. */

	/*
	 * The `strfdinsert' structure must be defined, including at least
	 * the following members.
	 */
	struct strfdinsert sf;

	(void)sf.ctlbuf;	/* The control portion of the message. */
	(void)sf.databuf;	/* The data portion of the message. */
	(void)sf.flags;		/* RS_HIPRI or 0. */
	(void)sf.fildes;	/* File descriptor of the other STREAM. */
	(void)sf.offset;	/* Relative location of the stored value. */

	/*
	 * The `strioctl' structure must be defined, including at least
	 * the following members.
	 */
	struct strioctl si;

	(void)si.ic_cmd;	/* ioctl() command. */
	(void)si.ic_timout;	/* Timeout for response. */
	(void)si.ic_len;	/* Length of data. */
	(void)si.ic_dp;		/* Pointer to buffer. */

	/*
	 * The `strrecvfd' structure must be defined, including at least
	 * the following members.
	 */
	struct strrecvfd sr;

	(void)sr.fda;	/* Received file descriptor. */
	(void)sr.uid;	/* UID of sender. */
	(void)sr.gid;	/* GID of sender. */

	/*
	 * The `str_list' structure must be defined, including at least
	 * the following members.
	 */
	struct str_list sl;

	(void)sl.sl_nmods;	/* Number of STREAMS module names. */
	(void)sl.sl_modlist;	/* STREAMS module names. */

	/*
	 * The `str_mlist' structure must be defined, including at least
	 * the following member.
	 */
	struct str_mlist sm;
	(void)sm.l_name;	/* A STREAMS module name. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
