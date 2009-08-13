all:    t_poll

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_poll: t_poll.c
	$(CC) $(CCFLAGS) $(LIB) t_poll.c -o t_poll

clean:
	git clean -f

run:
	@printf "t_poll: "
	@-./t_poll
