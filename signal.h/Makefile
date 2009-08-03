all:    t_signal

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_signal: t_signal.c
	$(CC) $(CCFLAGS) $(LIB) t_signal.c -o t_signal

clean:
	git clean -f

run:
	@printf "t_signal: "
	@-./t_signal
