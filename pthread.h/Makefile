all:    t_pthread_barrier_init	\
	t_pthread_barrier_wait	\
	t_pthread_barrierattr_init

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lthread_xu

t_pthread_barrier_init: t_pthread_barrier_init.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_barrier_init.c -o t_pthread_barrier_init

t_pthread_barrier_wait: t_pthread_barrier_wait.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_barrier_wait.c -o t_pthread_barrier_wait

t_pthread_barrierattr_init: t_pthread_barrierattr_init.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_barrierattr_init.c -o t_pthread_barrier_attr

clean:
	git clean -f

run:
	@printf "t_pthread_barrier_init: "
	@-./t_pthread_barrier_init

	@printf "t_pthread_barrier_wait: "
	@-./t_pthread_barrier_wait

`	@printf "t_pthread_barrierattr_init: "
	@-./t_pthread_barrierattr_init