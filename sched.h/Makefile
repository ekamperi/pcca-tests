all:	t_sched_getparam	\
	t_sched_rr_get_interval

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_sched_getparam: t_sched_getparam.c
	$(CC) $(CCFLAGS) $(LIB) t_sched_getparam.c -o t_sched_getparam

t_sched_rr_get_interval: t_sched_rr_get_interval.c
	$(CC) $(CCFLAGS) $(LIB) t_sched_rr_get_interval.c -o t_sched_rr_get_interval

clean:
	git clean -f

run:
	@printf "t_sched_getparam: "
	@-./t_sched_getparam

	@printf "t_sched_rr_get_interval: "
	@-./t_sched_rr_get_interval
