regex.h

_POSIX_C_SOURCE 200112L {
	# Values for the cflags parameter to the regcomp() function.
	REG_EXTENDED
	REG_ICASE
	REG_NOSUB
	REG_NEWLINE

	# Values for the eflags parameter to the regexec() function.
	REG_NOTBOL
	REG_NOTEOL

	# Error return values.
	REG_NOMATCH
	REG_BADPAT
	REG_ECOLLATE
	REG_ECTYPE
	REG_EESCAPE
	REG_ESUBREG
	REG_EBRACK
	REG_EPAREN
	REG_EBRACE
	REG_BADBR
	REG_ERANGE
	REG_ESPACE
	REG_BADRPT
	REG_ENOSYS
}
