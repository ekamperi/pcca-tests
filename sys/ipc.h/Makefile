all:    t_ipc

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_ipc: t_ipc.c
	$(CC) $(CCFLAGS) $(LIB) t_ipc.c -o t_ipc

clean:
	git clean -f

run:
	@printf "t_ipc: "
	@-./t_ipc
