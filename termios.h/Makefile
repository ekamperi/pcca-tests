all:	t_tcgetattr	\
	t_tcgetsid	\
	t_termios	\

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_tcgetattr: t_tcgetattr.c
	$(CC) $(CCFLAGS) $(LIB) t_tcgetattr.c -o t_tcgetattr

t_tcgetsid: t_tcgetsid.c
	$(CC) $(CCFLAGS) $(LIB) t_tcgetsid.c -o t_tcgetsid

t_termios: t_termios.c
	$(CC) $(CCFLAGS) $(LIB) t_termios.c -o t_termios

clean:
	git clean -f

run:
	@printf "t_tcgetattr: "
	@-./t_tcgetattr

	@printf "t_tcgetsid: "
	@-./t_tcgetsid

	@printf "t_termios: "
	@-./t_termios
