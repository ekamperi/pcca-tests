netinet/in.h

_POSIX_C_SOURCE 200112L {
	# Values of the level argument of getsockopt() and setsockopt().
	IPPROTO_IP
	IPPROTO_IPV6
	IPPROTO_ICMP
	IPPROTO_RAW
	IPPROTO_TCP
	IPPROTO_UDP

	# Destination addresses for connect(), sendmsg(), and sendto().
	INADDR_ANY
	INADDR_BROADCAST

	# Length of the string form for IP (to help applications declare
	# buffers of the proper size to store IPv4 addresses in string form.
	INET_ADDRSTRLEN

	# For use in the option_name argument in the getsockopt() or setsockopt()
	# functions at protocol level IPPROTO_IPV6.
	IPV6_JOIN_GROUP
	IPV6_LEAVE_GROUP
	IPV6_MULTICAST_HOPS
	IPV6_MULTICAST_IF
	IPV6_MULTICAST_LOOP
	IPV6_UNICAST_HOPS
	IPV6_V6ONLY

	# Macros that test for special IPv6 addresses.
	IN6_IS_ADDR_UNSPECIFIED
	IN6_IS_ADDR_LOOPBACK
	IN6_IS_ADDR_MULTICAST
	IN6_IS_ADDR_LINKLOCAL
	IN6_IS_ADDR_SITELOCAL
	IN6_IS_ADDR_V4MAPPED
	IN6_IS_ADDR_V4COMPAT
	IN6_IS_ADDR_MC_NODELOCAL
	IN6_IS_ADDR_MC_LINKLOCAL
	IN6_IS_ADDR_MC_SITELOCAL
	IN6_IS_ADDR_MC_ORGLOCAL
	IN6_IS_ADDR_MC_GLOBAL

	# Used to initialize a variable of type struct in6_addr
	# to the IPv6 wildcard address.
	IN6ADDR_ANY_INIT
}
