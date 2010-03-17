all:	t_setsockopt	\
	t_socket

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_setsockopt: t_setsockopt.c
	$(CC) $(CCFLAGS) t_setsockopt.c -o t_setsockopt

t_socket: t_socket.c
	$(CC) $(CCFLAGS) t_socket.c -o t_socket

clean:
	git clean -f

run:
	@printf "t_setsockopt: "
	@-./t_setsockopt

	@printf "t_socket: "
	@-./t_socket
