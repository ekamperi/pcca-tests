all:	t_lstat		\
	t_mkfifo	\
	t_mkfifo2	\
	t_stat		\
	t_umask

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_lstat: t_lstat.c
	$(CC) $(CCFLAGS) t_lstat.c -o t_lstat

t_mkfifo: t_mkfifo.c
	$(CC) $(CCFLAGS) t_mkfifo.c -o t_mkfifo

t_mkfifo2: t_mkfifo2.c
	$(CC) $(CCFLAGS) t_mkfifo2.c -o t_mkfifo2

t_stat: t_stat.c
	$(CC) $(CCFLAGS) t_stat.c -o t_stat

t_umask: t_umask.c
	$(CC) $(CCFLAGS) t_umask.c -o t_umask

clean:
	git clean -f

run:
	@printf "t_lstat: "
	@-./t_lstat

	@printf "t_mkfifo: "
	@-./t_mkfifo

	@printf "t_mkfifo2: "
	@-./t_mkfifo2

	@printf "t_stat: "
	@-./t_stat

	@printf "t_umask: "
	@-./t_umask
