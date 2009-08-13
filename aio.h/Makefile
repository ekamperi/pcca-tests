all:    t_aio	\

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lrt

t_aio: t_aio.c
	$(CC) $(CCFLAGS) $(LIB) t_aio.c -o t_aio

clean:
	git clean -f

run:
	@printf "t_aio: "
	@-./t_aio
