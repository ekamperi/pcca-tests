all:    t_minvalues

CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_ftw: t_minvalues
	$(CC99) $(CCFLAGS) t_minvalues.c -o t_minvalues

clean:
	git clean -f

run:
	@printf "t_minvalues: "
	@-./t_minvalues
