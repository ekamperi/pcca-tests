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

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(void)
{
	/*
	 * The `sockaddr' structure must be defined, including at least
	 * the following members.
	 */
	struct sockaddr sa;

	(void)sa.sa_family;	/* Address family. */
	(void)sa.sa_data;	/* Socket address (variable-length data). */

	/*
	 * The `sockaddr_storage' structure must be defined, including at least
	 * the following members.
	 */
	struct sockaddr_storage ss;

	(void)ss.ss_family;

	/*
	 * The `msghdr' structure must be defined, including at least
	 * the following members.
	 */
	struct msghdr msg;

	(void)msg.msg_name;	/* Optional address. */
	(void)msg.msg_namelen;	/* Size of address. */
	(void)msg.msg_iov;	/* Scatter/gather array. */
	(void)msg.msg_iovlen;	/* Members in msg_iov. */
	(void)msg.msg_control;	/* Ancillary data; see below. */
	(void)msg.msg_controllen; /*Anc cillary data buffer len. */
	(void)msg.msg_flags;	/* Flags on received message. */

	/*
	 * The iovec structure must be defined.
	 * (see <sys/uio.h>)
	 */
	struct iovec iov;

	/*
	 * The `cmsghdr' structure must be defined, including at least
	 * the following members.
	 */
	struct cmsghdr cmsg;

	(void)cmsg.cmsg_len;	/* Data byte count, including the cmsghdr. */
	(void)cmsg.cmsg_level;	/* Originating protocol. */
	(void)cmsg.cmsg_type;	/* Protocol-specific type. */

	/*
	 * The `linger' structure must be defined, including at least
	 * the following members.
	 */
	struct linger l;

	(void)l.l_onoff;	/* Whether linger option is enabled. */
	(void)l.l_linger;	/* Linger time, in seconds. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
