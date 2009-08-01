all:	t_getgrid	\
	t_grp

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_getgrid: t_getgrid.c
	$(CC) $(CCFLAGS) $(LIB) t_getgrid.c -o t_getgrid

t_grp: t_grp.c
	$(CC) $(CCFLAGS) $(LIB) t_grp.c -o t_grp

clean:
	git clean -f

run:
	@printf "t_getgrid: "
	@-./t_getgrid

	@printf "t_grp: "
	@-./t_grp
