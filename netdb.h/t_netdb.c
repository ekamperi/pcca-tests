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

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `hostent' structure must be defined, including at least the
	 * following members.
	 */
	struct hostent h;

	(void)h.h_name;		/* Official name of the host. */
	(void)h.h_aliases;	/* A pointer to an array of pointers to
				   alternative host names, terminated by a
				   null pointer. */
	(void)h.h_addrtype;	/* Address type. */
	(void)h.h_length;	/* The length, in bytes, of the address. */
	(void)h.h_addr_list;	/* A pointer to an array of pointers to network
				   addresses (in network byte order) for the host,
				   terminated by a null pointer. */

	/*
	 * The `netent' structure must be defined, including at least the
	 * following members.
	 */
	struct netent n;

	(void)n.n_name;		/* Official, fully-qualified (including the
				   domain) name of the host. */
	(void)n.n_aliases;	/* A pointer to an array of pointers to
				   alternative network names, terminated by a
				   null pointer. */
	(void)n.n_addrtype;	/* The address type of the network. */
	(void)n.n_net;		/* The network number, in host byte order. */

	/*
	 * The `protoent' structure must be defined, including at least the
	 * following members.
	 */
	struct protoent p;
	(void)p.p_name;		/* Official name of the protocol. */
	(void)p.p_aliases;	/* A pointer to an array of pointers to
				   alternative protocol names, terminated by
				   a null pointer. */
	(void)p.p_proto;	/* The protocol number. */

	/*
	 * The `servent' structure must be defined, including at least the
	 * following members.
	 */
	struct servent s;
	(void)s.s_name;		/* Official name of the service. */
	(void)s.s_aliases;	/* A pointer to an array of pointers to
				   alternative service names, terminated by
				   a null pointer. */
	(void)s.s_port;		/* The port number at which the service
				   resides, in network byte order. */
	(void)s.s_proto;	/* The name of the protocol to use when
				   contacting the service. */

	/*
	 * The `addrinfo' structure must be defined, including at least the
	 * following members.
	 */
	struct addrinfo ai;

	(void)ai.ai_flags;	/* Input flags. */
	(void)ai.ai_family;	/* Address family of socket. */
	(void)ai.ai_socktype;	/* Socket type. */
	(void)ai.ai_protocol;	/* Protocol of socket. */
	(void)ai.ai_addrlen;	/* Length of socket address. */
	(void)ai.ai_addr;	/* Socket address of socket. */
	(void)ai.ai_canonname;	/* Canonical name of service location. */
	(void)ai.ai_next;	/* Pointer to next in list. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
