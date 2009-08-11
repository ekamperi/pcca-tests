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
