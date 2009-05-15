all: t_mq_open t_mq_close t_mq_parent_child t_mq_send t_mq_simple_send \
     t_mq_simple_recv

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lrt

t_mq_open: t_mq_open.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_open.c -o t_mq_open

t_mq_close: t_mq_close.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_close.c -o t_mq_close

t_mq_parent_child: t_mq_parent_child.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_parent_child.c -o t_mq_parent_child

t_mq_send: t_mq_send.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_send.c -o t_mq_send

t_mq_simple_send: t_mq_simple_send.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_simple_send.c -o t_mq_simple_send

t_mq_simple_recv: t_mq_simple_recv.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_simple_recv.c -o t_mq_simple_recv

clean:
	git clean -f





