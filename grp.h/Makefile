all:	t_getgrent	\
	t_getgrgid	\
	t_getgrnam	\
	t_getgrnam_r	\
	t_grp

CC=gcc
CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_getgrent: t_getgrent.c
	$(CC99) $(CCFLAGS) $(LIB) t_getgrent.c -o t_getgrent

t_getgrgid: t_getgrgid.c
	$(CC) $(CCFLAGS) $(LIB) t_getgrgid.c -o t_getgrgid

t_getgrnam: t_getgrnam.c
	$(CC) $(CCFLAGS) $(LIB) t_getgrnam.c -o t_getgrnam

t_getgrnam_r: t_getgrnam_r.c
	$(CC99) $(CCFLAGS) $(LIB) t_getgrnam_r.c -o t_getgrnam_r

t_grp: t_grp.c
	$(CC) $(CCFLAGS) $(LIB) t_grp.c -o t_grp

clean:
	git clean -f

run:
	@printf "t_getgrent: "
	@-./t_getgrent

	@printf "t_getgrgid: "
	@-./t_getgrgid

	@printf "t_getgrnam: "
	@-./t_getgrnam

	@printf "t_getgrnam_r: "
	@-./t_getgrnam_r

	@printf "t_grp: "
	@-./t_grp
