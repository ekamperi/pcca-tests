all:    t_un

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_un: t_un.c
	$(CC) $(CCFLAGS) $(LIB) t_un.c -o t_un

clean:
	git clean -f

run:
	@printf "t_un: "
	@-./t_un
