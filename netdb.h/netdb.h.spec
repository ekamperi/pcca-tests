netdb.h

_POSIX_C_SOURCE 200112L {
	# Integer constants for use in the flags field of the addrinfo
	# structure.
	AI_PASSIVE
	AI_CANONNAME
	AI_NUMERICHOST
	AI_NUMERICSERV
	AI_V4MAPPED
	AI_ALL
	AI_ADDRCONFIG

	# Integer constants for use in the flags argument to getnameinfo()
	NI_NOFQDN
	NI_NUMERICHOST
	NI_NAMEREQD
	NI_NUMERICSERV
	NI_NUMERICSCOPE
	NI_DGRAM

	# Address Information Errors
	EAI_AGAIN
	EAI_BADFLAGS
	EAI_FAIL
	EAI_FAMILY
	EAI_MEMORY
	EAI_NONAME
	EAI_SERVICE
	EAI_SOCKTYPE
	EAI_SYSTEM
	EAI_OVERFLOW
}
