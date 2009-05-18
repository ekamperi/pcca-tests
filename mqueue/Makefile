all:    t_mq_open		\
	t_mq_openclose		\
	t_mq_close		\
	t_mq_parent_child	\
	t_mq_parent_multmsg	\
	t_mq_send		\
	t_mq_setattr		\

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lrt

t_mq_open: t_mq_open.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_open.c -o t_mq_open

t_mq_openclose: t_mq_openclose.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_openclose.c -o t_mq_openclose

t_mq_close: t_mq_close.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_close.c -o t_mq_close

t_mq_parent_child: t_mq_parent_child.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_parent_child.c -o t_mq_parent_child

t_mq_parent_multmsg: t_mq_parent_multmsg.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_parent_multmsg.c -o t_mq_parent_multmsg

t_mq_send: t_mq_send.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_send.c -o t_mq_send

t_mq_setattr: t_mq_setattr.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_setattr.c -o t_mq_setattr

clean:
	git clean -f
