all:	t_cpio

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_cpio: t_cpio.c
	$(CC) $(CCFLAGS) $(LIB) t_cpio.c -o t_cpio

clean:
	git clean -f

run:
	@printf "t_cpio: "
	@-./t_cpio
