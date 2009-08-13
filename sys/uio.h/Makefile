all:	t_uio

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_uio: t_uio.c
	$(CC) $(CCFLAGS) $(LIB) t_uio.c -o t_uio

clean:
	git clean -f

run:
	@printf "t_uio: "
	@-./t_uio
