all:    t_utime

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_utime: t_utime.c
	$(CC) $(CCFLAGS) $(LIB) t_utime.c -o t_utime

clean:
	git clean -f

run:
	@printf "t_utime: "
	@-./t_utime
