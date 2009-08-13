all:    t_ftw

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_ftw: t_ftw.c
	$(CC) $(CCFLAGS) $(LIB) t_ftw.c -o t_ftw

clean:
	git clean -f

run:
	@printf "t_ftw: "
	@-./t_ftw
