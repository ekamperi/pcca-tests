all:	t_clearerr	\
	t_ctermid	\
	t_fileno	\
	t_stdio		\
	t_tmpnam

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_clearerr: t_clearerr.c
	$(CC) $(CCFLAGS) $(LIB) t_clearerr.c -o t_clearerr

t_ctermid: t_ctermid.c
	$(CC) $(CCFLAGS) $(LIB) t_ctermid.c -o t_ctermid

t_fileno: t_fileno.c
	$(CC) $(CCFLAGS) $(LIB) t_fileno.c -o t_fileno

t_stdio: t_stdio.c
	$(CC) $(CCFLAGS) $(LIB) t_stdio.c -o t_stdio

t_tmpnam: t_tmpnam.c
	$(CC) $(CCFLAGS) $(LIB) t_tmpnam.c -o t_tmpnam

clean:
	git clean -f

run:
	@printf "t_clearerr: "
	@-./t_clearerr

	@printf "t_ctermid: "
	@-./t_ctermid

	@printf "t_fileno: "
	@-./t_fileno

	@printf "t_stdio: "
	@-./t_stdio

	@printf "t_tmpnam: "
	@-./t_tmpnam
