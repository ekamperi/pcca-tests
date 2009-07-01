all:	t_ctermid \

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_ctermid: t_ctermid.c
	$(CC) $(CCFLAGS) $(LIB) t_ctermid.c -o t_ctermid

clean:
	git clean -f

run:
	@printf "t_ctermid: "
	@-./t_ctermid
