sys/socket.h

_POSIX_C_SOURCE 200112L {
	SCM_RIGHTS

	CMSG_DATA
	CMSG_NXTHDR
	CMSG_FIRSTHDR

	SOCK_DGRAM
	SOCK_RAW
	SOCK_SEQPACKET
	SOCK_STREAM

	# For use as the level argument of setsockopt() and getsockopt().
	SOL_SOCKET

	# For use as the option_name argument in getsockopt() or setsockopt()
	# calls.
	SO_ACCEPTCONN
	SO_BROADCAST
	SO_DEBUG
	SO_DONTROUTE
	SO_ERROR
	SO_KEEPALIVE
	SO_LINGER
	SO_OOBINLINE
	SO_RCVBUF
	SO_RCVLOWAT
	SO_RCVTIMEO
	SO_REUSEADDR
	SO_SNDBUF
	SO_SNDLOWAT
	SO_SNDTIMEO
	SO_TYPE

	# Maximum backlog queue length which may be specified by the backlog
	# field of the listen() function.
	SOMAXCONN

	# Valid values for the msg_flags field in the msghdr structure, or the
	# flags parameter in recvfrom(), recvmsg(), sendmsg(), or sendto()
	# calls.
	MSG_CTRUNC
	MSG_DONTROUTE
	MSG_EOR
	MSG_OOB
	MSG_PEEK
	MSG_TRUNC
	MSG_WAITALL


	AF_INET
	AF_INET6
	AF_UNIX
	AF_UNSPEC

	SHUT_RD
	SHUT_RDWR
	SHUT_WR
}
