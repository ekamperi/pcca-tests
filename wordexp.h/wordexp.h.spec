wordexp.h

_POSIX_C_SOURCE 200112L {
	# Flags argument to the wordexp() function.
	WRDE_APPEND
	WRDE_DOOFFS
	WRDE_NOCMD
	WRDE_REUSE
	WRDE_SHOWERR
	WRDE_UNDEF

	# Error return values.
	WRDE_BADCHAR
	WRDE_BADVAL
	WRDE_CMDSUB
	WRDE_NOSPACE
	WRDE_NOSYS
	WRDE_SYNTAX
}

_XOPEN_SOURCE 600 {
	# Obsolescent.
	WRDE_NOSYS
}
