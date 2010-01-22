all:	t_mq_ambig			\
	t_mq_close			\
	t_mq_notify_invsigno		\
	t_mq_notify_simple		\
	t_mq_open			\
	t_mq_open_close			\
	t_mq_open_umask			\
	t_mq_parent_child		\
	t_mq_parent_child_multmsg	\
	t_mq_prio			\
	t_mq_select			\
	t_mq_send			\
	t_mq_send2			\
	t_mq_send3			\
	t_mq_setattr			\
	t_mq_timedsend			\
	t_mq_timedsend2			\
	t_mq_timedreceive_timeout	\
	t_mq_timedsend_timeout		\

CC=gcc
CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lrt

t_mq_ambig: t_mq_ambig.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_ambig.c -o t_mq_ambig

t_mq_close: t_mq_close.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_close.c -o t_mq_close

t_mq_notify_invsigno: t_mq_notify_invsigno.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_notify_invsigno.c -o t_mq_notify_invsigno

t_mq_notify_simple: t_mq_notify_simple.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_notify_simple.c -o t_mq_notify_simple

t_mq_open: t_mq_open.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_open.c -o t_mq_open

t_mq_open_close: t_mq_open_close.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_open_close.c -o t_mq_open_close

t_mq_open_umask: t_mq_open_umask.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_open_umask.c -o t_mq_open_umask

t_mq_parent_child: t_mq_parent_child.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_parent_child.c -o t_mq_parent_child

t_mq_parent_child_multmsg: t_mq_parent_child_multmsg.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_parent_child_multmsg.c -o t_mq_parent_child_multmsg

t_mq_prio: t_mq_prio.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_prio.c -o t_mq_prio

t_mq_select: t_mq_select.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_select.c -o t_mq_select

t_mq_send: t_mq_send.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_send.c -o t_mq_send

t_mq_send2: t_mq_send2.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_send2.c -o t_mq_send2

t_mq_send3: t_mq_send3.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_send3.c -o t_mq_send3

t_mq_setattr: t_mq_setattr.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_setattr.c -o t_mq_setattr

t_mq_timedsend: t_mq_timedsend.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_timedsend.c -o t_mq_timedsend

t_mq_timedsend2: t_mq_timedsend2.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_timedsend2.c -o t_mq_timedsend2

t_mq_timedreceive_timeout: t_mq_timedreceive_timeout.c
	$(CC99) $(CCFLAGS) $(LIB) t_mq_timedreceive_timeout.c -o t_mq_timedreceive_timeout

t_mq_timedsend_timeout: t_mq_timedsend_timeout.c
	$(CC99) $(CCFLAGS) $(LIB) t_mq_timedsend_timeout.c -o t_mq_timedsend_timeout

clean:
	git clean -f

run:
	@printf "t_mq_ambig: "
	@-./t_mq_ambig

	@printf "t_mq_close: "
	@-./t_mq_close

	@printf "t_mq_notify_invsigno: "
	@-./t_mq_notify_invsigno

	@printf "t_mq_notify_simple: "
	@-./t_mq_notify_simple

	@printf "t_mq_open: "
	@-./t_mq_open

	@printf "t_mq_open_close: "
	@-./t_mq_open_close

	@printf "t_mq_open_umask: "
	@-./t_mq_open_umask

	@printf "t_mq_parent_child: "
	@-./t_mq_parent_child

	@printf "t_mq_parent_child_multmsg: "
	@-./t_mq_parent_child_multmsg

	@printf "t_mq_prio: "
	@-./t_mq_prio

	@printf "t_mq_select: "
	@-./t_mq_select

	@printf "t_mq_send: "
	@-./t_mq_send

	@printf "t_mq_send2: "
	@-./t_mq_send2

	@printf "t_mq_send3: "
	@-./t_mq_send3

	@printf "t_mq_setattr: "
	@-./t_mq_setattr

	@printf "t_mq_timedsend: "
	@-./t_mq_timedsend

	@printf "t_mq_timedsend2: "
	@-./t_mq_timedsend2

	@printf "t_mq_timedreceive_timeout: "
	@-./t_mq_timedreceive_timeout

	@printf "t_mq_timedsend_timeout: "
	@-./t_mq_timedsend_timeout
