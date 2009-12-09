all:	t_ulimit

CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_ulimit: t_ulimit.c
	$(CC99) $(CCFLAGS) $(LIB) t_ulimit.c -o t_ulimit

clean:
	git clean -f

run:
	@printf "t_ulimit: "
	@-./t_ulimit
