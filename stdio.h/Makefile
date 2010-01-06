all:	t_clearerr	\
	t_ctermid	\
	t_ferror	\
	t_fileno	\
	t_flockfile	\
	t_stdio		\
	t_tempnam	\
	t_tmpfile

CC=gcc
CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_clearerr: t_clearerr.c
	$(CC) $(CCFLAGS) $(LIB) t_clearerr.c -o t_clearerr

t_ctermid: t_ctermid.c
	$(CC) $(CCFLAGS) $(LIB) t_ctermid.c -o t_ctermid

t_ferror: t_ferror.c
	$(CC) $(CCFLAGS) $(LIB) t_ferror.c -o t_ferror

t_fileno: t_fileno.c
	$(CC) $(CCFLAGS) $(LIB) t_fileno.c -o t_fileno

t_flockfile: t_flockfile.c
	$(CC99) $(CCFLAGS) -lpthread t_flockfile.c -o t_flockfile

t_stdio: t_stdio.c
	$(CC) $(CCFLAGS) $(LIB) t_stdio.c -o t_stdio

t_tempnam: t_tempnam.c
	$(CC) $(CCFLAGS) $(LIB) t_tempnam.c -o t_tempnam

t_tmpfile: t_tmpfile.c
	$(CC) $(CCFLAGS) $(LIB) t_tmpfile.c -o t_tmpfile

clean:
	git clean -f

run:
	@printf "t_clearerr: "
	@-./t_clearerr

	@printf "t_ctermid: "
	@-./t_ctermid

	@printf "t_ferror: "
	@-./t_ferror

	@printf "t_fileno: "
	@-./t_fileno

	@printf "t_flockfile: "
	@-./t_flockfile

	@printf "t_stdio: "
	@-./t_stdio

	@printf "t_tempnam: "
	@-./t_tempnam

	@printf "t_tmpfile: "
	@-./t_tmpfile
