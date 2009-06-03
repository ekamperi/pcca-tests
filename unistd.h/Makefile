all:	t_access	\
	t_isatty	\
	t_ttyname	\
#	t_ttyname_r

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_access: t_access.c
	$(CC) $(CCFLAGS) $(LIB) t_access.c -o t_access

t_isatty: t_isatty.c
	$(CC) $(CCFLAGS) $(LIB) t_isatty.c -o t_isatty

t_ttyname: t_ttyname.c
	$(CC) $(CCFLAGS) $(LIB) t_ttyname.c -o t_ttyname

t_ttyname_r: t_ttyname_r.c
	$(CC) $(CCFLAGS) $(LIB) t_ttyname_r.c -o t_ttyname_r

clean:
	git clean -f

run:
	@printf "t_access: "
	@-./t_access

	@printf "t_isatty: "
	@-./t_isatty

	@printf "t_ttyname: "
	@-./t_ttyname

#	@printf "t_ttyname_r: "
#	@-./t_ttyname_r
