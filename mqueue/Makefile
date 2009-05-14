all: t_mq_open t_mq_close t_mq_parent_child t_mq_send t_mq_simple_send \
     t_mq_simple_recv

CC=gcc
LIB=-lrt

t_mq_open: t_mq_open.c
	$(CC) $(LIB) t_mq_open.c -o t_mq_open

t_mq_close: t_mq_close.c
	$(CC) $(LIB) t_mq_close.c -o t_mq_close

t_mq_parent_child: t_mq_parent_child.c
	$(CC) $(LIB) t_mq_parent_child.c -o t_mq_parent_child

t_mq_send: t_mq_send.c
	$(CC) $(LIB) t_mq_send.c -o t_mq_send

t_mq_simple_send: t_mq_simple_send.c
	$(CC) $(LIB) t_mq_simple_send.c -o t_mq_simple_send

t_mq_simple_recv: t_mq_simple_recv.c
	$(CC) $(LIB) t_mq_simple_recv.c -o t_mq_simple_recv

clean:
	rm -f t_mq_*[^.c]
	rm -f *~
	rm -f \#*
	rm -f a.out


