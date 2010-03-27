all:    t_signal		\
	t_signal_altstack	\

CC=gcc
CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_signal: t_signal.c
	$(CC) $(CCFLAGS) $(LIB) t_signal.c -o t_signal

t_signal_altstack: t_signal_altstack.c
	$(CC99) $(CCFLAGS) $(LIB) t_signal_altstack.c -o t_signal_altstack

clean:
	git clean -f

run:
	@printf "t_signal: "
	@-./t_signal
