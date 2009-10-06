all:	t_ffs

CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_ffs: t_ffs.c
	$(CC99) $(CCFLAGS) t_ffs.c -o t_ffs

clean:
	git clean -f

run:
	@printf "t_ffs: "
	@-./t_ffs
