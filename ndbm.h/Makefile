all:	t_ndbm

CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_ndbm: t_ndbm.c
	$(CC99) $(CCFLAGS) $(LIB) t_ndbm.c -o t_ndbm

clean:
	git clean -f

run:
	@printf "t_ndbm: "
	@-./t_ndbm
