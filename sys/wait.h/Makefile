all:	t_abort

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_abort: t_abort.c
	$(CC) $(CCFLAGS) t_abort.c -o t_abort

clean:
	git clean -f

run:
	@printf "t_abort: "
	@-./t_abort
