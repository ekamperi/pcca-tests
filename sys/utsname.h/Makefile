all:    t_uname

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_uname: t_uname.c
	$(CC) $(CCFLAGS) t_uname.c -o t_uname

clean:
	git clean -f

run:
	@printf "t_uname: "
	@-./t_uname
