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
