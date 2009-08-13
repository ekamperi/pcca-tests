all:	t_netdb

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_netdb: t_netdb.c
	$(CC) $(CCFLAGS) $(LIB) t_netdb.c -o t_netdb

clean:
	git clean -f

run:
	@printf "t_netdb: "
	@-./t_netdb
