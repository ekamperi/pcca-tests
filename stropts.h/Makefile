all:    t_stropts

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_stropts: t_stropts.c
	$(CC) $(CCFLAGS) $(LIB) t_stropts.c -o t_stropts

clean:
	git clean -f

run:
	@printf "t_stropts: "
	@-./t_stropts
