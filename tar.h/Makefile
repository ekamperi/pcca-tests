all:	t_tar

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_tar: t_tar.c
	$(CC) $(CCFLAGS) $(LIB) t_tar.c -o t_tar

clean:
	git clean -f

run:
	@printf "t_tar: "
	@-./t_tar
