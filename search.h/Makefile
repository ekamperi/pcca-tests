all:    t_htable	\

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_table: t_htable.c
	$(CC) $(CCFLAGS) $(LIB) t_htable.c -o t_htable

clean:
	git clean -f

run:
	@printf "t_htable: "
	@-./t_htable
