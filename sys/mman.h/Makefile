all:	t_mlockall	\
	t_shm

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lrt

t_mlockall: t_mlockall.c
	$(CC) $(CCFLAGS) t_mlockall.c -o t_mlockall

t_shm: t_shm.c
	$(CC) $(CCFLAGS) $(LIB) t_shm.c -o t_shm

clean:
	git clean -f

run:
	@printf "t_mlockall: "
	@-./t_mlockall

	@printf "t_shm: "
	@-./t_shm
