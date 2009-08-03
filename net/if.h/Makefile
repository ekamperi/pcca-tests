all:	t_if

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_if: t_if.c
	$(CC) $(CCFLAGS) $(LIB) t_if.c -o t_if

clean:
	git clean -f

run:
	@printf "t_if: "
	@-./t_if
