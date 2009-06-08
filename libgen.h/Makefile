all:    t_dirname	\

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_dirname: t_dirname.c
	$(CC) $(CCFLAGS) $(LIB) t_dirname.c -o t_dirname

clean:
	git clean -f

run:
	@printf "t_dirname: "
	@-./t_dirname
