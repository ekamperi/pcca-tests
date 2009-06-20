all:    t_mq_open		\
	t_mq_openclose		\
	t_mq_close		\
	t_mq_parallel		\
	t_mq_parent_child	\
	t_mq_parent_child_multmsg	\
	t_mq_prio		\
	t_mq_select		\
	t_mq_send		\
	t_mq_setattr		\
	t_mq_sysctl		\
	t_mq_timedsend

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

t_mq_parallel: t_mq_parallel.c
	$(CC) $(CCFLAGS) $(LIB) -lpthread t_mq_parallel.c -o t_mq_parallel

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

t_mq_setattr: t_mq_setattr.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_setattr.c -o t_mq_setattr

t_mq_sysctl: t_mq_sysctl.c
	$(CC) $(CCFLAGS) t_mq_sysctl.c -o t_mq_sysctl

t_mq_timedsend: t_mq_timedsend.c
	$(CC) $(CCFLAGS) $(LIB) t_mq_timedsend.c -o t_mq_timedsend

clean:
	git clean -f

run:
	@printf "t_mq_open: "
	@-./t_mq_open

	@printf "t_mq_openclose: "
	@-./t_mq_openclose

	@printf "t_mq_close: "
	@-./t_mq_close

        @printf "t_mq_parallel: "
	@-./t_mq_parallel

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

	@printf "t_mq_setattr: "
	@-./t_mq_setattr

	@printf "t_mq_sysctl: "
	@-./t_mq_sysctl

	@printf "t_mq_timedsend: "
	@-./t_mq_timedsend
