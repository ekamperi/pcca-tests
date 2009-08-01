all:    t_fcntl

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_fcntl: t_fcntl.c
	$(CC) $(CCFLAGS) $(LIB) t_fcntl.c -o t_fcntl

clean:
	git clean -f

run:
	@printf "t_fcntl: "
	@-./t_fcntl
