all:	t_clock_getres	\
	t_time

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_clock_getres: t_clock_getres.c
	$(CC) $(CCFLAGS) t_clock_getres.c -o t_clock_getres

t_time: t_time.c
	$(CC) $(CCFLAGS) $(LIB) t_time.c -o t_time

clean:
	git clean -f

run:
	@printf "t_clock_getres: "
	@-./t_clock_getres

	@printf "t_time: "
	@-./t_time
