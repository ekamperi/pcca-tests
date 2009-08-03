all:    t_in

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_in: t_in.c
	$(CC) $(CCFLAGS) $(LIB) t_in.c -o t_in

clean:
	git clean -f

run:
	@printf "t_in: "
	@-./t_in
