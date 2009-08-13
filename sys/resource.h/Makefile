all:    t_getpriority	\
	t_getrlimit	\
	t_getrusage	\
	t_setpriority	\
	t_setrlimit	\

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_getpriority: t_getpriority.c
	$(CC) $(CCFLAGS) $(LIB) t_getpriority.c -o t_getpriority

t_getrlimit: t_getrlimit.c
	$(CC) $(CCFLAGS) $(LIB) t_getrlimit.c -o t_getrlimit

t_getrusage: t_getrusage.c
	$(CC) $(CCFLAGS) $(LIB) t_getrusage.c -o t_getrusage

t_setpriority: t_setpriority.c
	$(CC) $(CCFLAGS) $(LIB) t_setpriority.c -o t_setpriority

t_setrlimit: t_setrlimit.c
	$(CC) $(CCFLAGS) $(LIB) t_setrlimit.c -o t_setrlimit

clean:
	git clean -f

run:
	@printf "t_getpriority: "
	@-./t_getpriority

	@printf "t_getrlimit: "
	@-./t_getrlimit

	@printf "t_getrusage: "
	@-./t_getrusage

	@printf "t_setpriority: "
	@-./t_setpriority

	@printf "t_setrlimit: "
	@-./t_setrlimit
