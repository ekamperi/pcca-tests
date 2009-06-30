all:	t_fstatvfs \
	t_statvfs

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_fstatvfs: t_fstatvfs.c
	$(CC) $(CCFLAGS) $(LIB) t_fstatvfs.c -o t_fstatvfs

t_statvfs: t_statvfs.c
	$(CC) $(CCFLAGS) $(LIB) t_statvfs.c -o t_statvfs

clean:
	git clean -f

run:
	@printf "t_fstatvfs: "
	@-./t_fstatvfs

	@printf "t_statvfs: "
	@-./t_statvfs
