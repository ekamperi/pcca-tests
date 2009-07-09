all:	t_dlopen

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_dlopen: t_dlopen.c
	$(CC) $(CCFLAGS) $(LIB) t_dlopen.c -o t_dlopen

clean:
	git clean -f

run:
	@printf "t_dlopen: "
	@-./t_dlopen
