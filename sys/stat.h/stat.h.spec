sys/stat.h

_XOPEN_SOURCE 600 {
	# File types
	S_IFMT
	S_IFBLK
	S_IFCHR
	S_IFIFO
	S_IFREG
	S_IFDIR
	S_IFLNK
	S_IFSOCK
	S_ISVTX
}

_POSIX_C_SOURCE 200112L {
	# File mode bits
	S_IRWXU
	S_IRUSR
	S_IWUSR
	S_IXUSR

	S_IRWXG
	S_IRGRP
	S_IWGRP
	S_IXGRP

	S_IRWXO
	S_IROTH
	S_IWOTH
	S_IXOTH

	S_ISUID
	S_ISGID

	# The following macros shall be provided to test whether a file
	# is of the specified type.
	S_ISBLK
	S_ISCHR
	S_ISDIR
	S_ISFIFO
	S_ISREG
	S_ISLNK
	S_ISSOCK

	S_TYPEISMQ
	S_TYPEISSEM
	S_TYPEISSHM

	S_TYPEISTMO
}
