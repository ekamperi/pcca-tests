all:	t_sem_circbuf	\
	t_sem_destroy	\
	t_sem_getvalue	\
	t_sem_init	\
	t_sem_init_pshared \
	t_sem_open	\
	t_sem_thr	\
	t_sem_timedwait	\
	t_sem_trywait

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lpthread

t_sem_circbuf: t_sem_circbuf.c
	$(CC) $(CCFLAGS) $(LIB) -lpthread t_sem_circbuf.c -o t_sem_circbuf

t_sem_destroy: t_sem_destroy.c
	$(CC) $(CCFLAGS) $(LIB) t_sem_destroy.c -o t_sem_destroy

t_sem_getvalue: t_sem_getvalue.c
	$(CC) $(CCFLAGS) $(LIB) t_sem_getvalue.c -o t_sem_getvalue

t_sem_init: t_sem_init.c
	$(CC) $(CCFLAGS) $(LIB) t_sem_init.c -o t_sem_init

t_sem_init_pshared: t_sem_init_pshared.c
	$(CC) $(CCFLAGS) $(LIB) t_sem_init_pshared.c -o t_sem_init_pshared

t_sem_open: t_sem_open.c
	$(CC) $(CCFLAGS) $(LIB) t_sem_open.c -o t_sem_open

t_sem_thr: t_sem_thr.c
	$(CC) $(CCFLAGS) $(LIB) -lpthread t_sem_thr.c -o t_sem_thr

t_sem_timedwait: t_sem_timedwait.c
	$(CC) $(CCFLAGS) $(LIB) t_sem_timedwait.c -o t_sem_timedwait

t_sem_trywait: t_sem_trywait.c
	$(CC) $(CCFLAGS) $(LIB) t_sem_trywait.c -o t_sem_trywait

clean:
	git clean -f

run:
	@printf "t_sem_circbuf: "
	@-./t_sem_circbuf

	@printf "t_sem_destroy: "
	@-./t_sem_destroy

	@printf "t_sem_getvalue: "
	@-./t_sem_getvalue

	@printf "t_sem_init: "
	@-./t_sem_init

	@printf "t_sem_init_pshared: "
	@-./t_sem_init_pshared

	@printf "t_sem_thr: "
	@-./t_sem_thr

	@printf "t_sem_timedwait: "
	@-./t_sem_timedwait

	@printf "t_sem_open: "
	@-./t_sem_open

	@printf "t_sem_trywait: "
	@-./t_sem_trywait
