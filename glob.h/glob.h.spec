glob.h

_POSIX_C_SOURCE 200112L {
	# The following constants are provided as values for the flags argument.
	GLOB_APPEND
	GLOB_DOOFFS
	GLOB_ERR
	GLOB_MARK
	GLOB_NOCHECK
	GLOB_NOESCAPE
	GLOB_NOSORT

	# The following constants are provided as error return values.
	GLOB_ABORTED
	GLOB_NOMATCH
	GLOB_NOSPACE
	GLOB_NOSYS
}

_XOPEN_SOURCE 600 {
	# This is marked obsolent as of Issue 6.
	GLOB_NOSYS
}
