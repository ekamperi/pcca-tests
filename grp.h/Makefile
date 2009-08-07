all:	t_getgrent	\
	t_getgrgid	\
	t_grp

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_getgrent: t_getgrent.c
	$(CC) $(CCFLAGS) $(LIB) t_getgrent.c -o t_getgrent

t_getgrgid: t_getgrgid.c
	$(CC) $(CCFLAGS) $(LIB) t_getgrgid.c -o t_getgrgid

t_grp: t_grp.c
	$(CC) $(CCFLAGS) $(LIB) t_grp.c -o t_grp

clean:
	git clean -f

run:
	@printf "t_getgrent: "
	@-./t_getgrent

	@printf "t_getgrgid: "
	@-./t_getgrgid

	@printf "t_grp: "
	@-./t_grp
