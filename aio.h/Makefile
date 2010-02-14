all:    t_aio		\
	t_aio_suspend	\

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lrt

t_aio: t_aio.c
	$(CC) $(CCFLAGS) $(LIB) t_aio.c -o t_aio

t_aio_suspend: t_aio_suspend.c
	$(CC) $(CCFLAGS) $(LIB) t_aio_suspend.c -o t_aio_suspend

clean:
	git clean -f

run:
	@printf "t_aio: "
	@-./t_aio

	@printf "t_aio_suspend: "
	@-./t_aio_suspend
