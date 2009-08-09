all:	t_mkfifo	\
	t_stat

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_mkfifo: t_mkfifo.c
	$(CC) $(CCFLAGS) $(LIB) t_mkfifo.c -o t_mkfifo

t_stat: t_stat.c
	$(CC) $(CCFLAGS) $(LIB) t_stat.c -o t_stat

clean:
	git clean -f

run:
	@printf "t_mkfifo: "
	@-./t_mkfifo

	@printf "t_stat: "
	@-./t_stat
