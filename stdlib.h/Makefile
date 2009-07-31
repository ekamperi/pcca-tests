all:	t_posix_memalign	\
	t_putenv		\

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=

t_posix_memalign: t_posix_memalign.c
	$(CC) $(CCFLAGS) $(LIB) t_posix_memalign.c -o t_posix_memalign

t_putenv: t_putenv.c
	$(CC) $(CCFLAGS) $(LIB) t_putenv.c -o t_putenv

t_stdlib: t_stdlib.c
	$(CC) $(CCFLAGS) $(LIB) t_stdlib.c -o t_stdlib

clean:
	git clean -f

run:
	@printf "t_posix_memalign: "
	@-./t_posix_memalign

	@printf "t_putenv: "
	@-./t_putenv

	@printf "t_stdlib: "
	@-./t_stdlib
