all:    t_longjmp

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_longjmp: t_longjmp.c
	$(CC) $(CCFLAGS) $(LIB) t_longjmp.c -o t_longjmp

clean:
	git clean -f

run:
	@printf "t_longjmp: "
	@-./t_longjmp
