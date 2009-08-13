all:	t_mq_parallel_threads	\
	t_mq_parallel_fork	\
	t_mq_sysctl

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lrt

t_mq_parallel_threads: t_mq_parallel_threads.c
	$(CC) $(CCFLAGS) $(LIB) -lpthread t_mq_parallel_threads.c -o t_mq_parallel_threads

t_mq_parallel_fork: t_mq_parallel_fork.c
	$(CC) $(CCFLAGS) $(LIB) -lpthread t_mq_parallel_fork.c -o t_mq_parallel_fork

t_mq_sysctl: t_mq_sysctl.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_sysctl.c -o t_mq_sysctl

clean:
	git clean -f
