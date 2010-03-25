all:	t_clock_getres	\
	t_time		\
	t_timer

CC=gcc
CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lrt

t_clock_getres: t_clock_getres.c
	$(CC) $(CCFLAGS) $(LIB) t_clock_getres.c -o t_clock_getres

t_time: t_time.c
	$(CC) $(CCFLAGS) $(LIB) t_time.c -o t_time

t_timer: t_timer.c
	$(CC99) $(CCFLAGS) $(LIB) t_timer.c -o t_timer

clean:
	git clean -f

run:
	@printf "t_clock_getres: "
	@-./t_clock_getres

	@printf "t_time: "
	@-./t_time

	@printf "t_timer: "
	@-./t_timer
