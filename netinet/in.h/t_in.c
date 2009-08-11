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

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `in_addr' structure must be defined, including at least
	 * the following member.
	 */
	struct in_addr s;

	(void)s.s_addr;

	/*
	 * The `sockaddr_in' structure must be defined, including at least
	 * the following members.
	 */
	struct sockaddr_in sin;

	(void)sin.sin_family;	/* AF_INET. */
	(void)sin.sin_port;	/* Port number. */
	(void)sin.sin_addr;	/* IP address. */

	/*
	 * The `in6_addr' structure must be defined, including at least
	 * the following member.
	 */
	struct in6_addr s6;
	(void)s6.s6_addr;

	/*
	 * The `sockaddr_in6' structure must be defined, including at least
	 * the following members.
	 */
	struct sockaddr_in6 sin6;

	(void)sin6.sin6_family;		/* AF_INET6. */
	(void)sin6.sin6_port;		/* Port number. */
	(void)sin6.sin6_flowinfo;	/* IPv6 traffic class and flow information. */
	(void)sin6.sin6_addr;		/* IPv6 address. */
	(void)sin6.sin6_scope_id;	/* Set of interfaces for a scope. */

	/*
	 * The `ipv6_mreq' structure must be defined, including at least
	 * the following members.
	 */
	struct ipv6_mreq ipv6mr;

	(void)ipv6mr.ipv6mr_multiaddr;	/* IPv6 multicast address. */
	(void)ipv6mr.ipv6mr_interface;	/* Interface index. */

	/* The following external variables must be declared. */
	(void)in6addr_any;
	(void)in6addr_loopback;

	printf("passed\n");

	return (EXIT_SUCCESS);
}
