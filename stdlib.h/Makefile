all:	t_basename		\
	t_posix_memalign	\
	t_putenv		\

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=

t_basename: t_basename.c
	$(CC) $(CCFLAGS) $(LIB) t_basename.c -o t_basename

t_fmaxf: t_posix_memalign.c
	$(CC) $(CCFLAGS) $(LIB) t_posix_memalign.c -o t_posix_memalign

t_fmaxl: t_putenv.c
	$(CC) $(CCFLAGS) $(LIB) t_putenv.c -o t_putenv

clean:
	git clean -f

run:
	@printf "t_basename......: "
	@-./t_basename

	@printf "t_posix_memalign: "
	@-./t_posix_memalign

	@printf "t_putenv........: "
	@-./t_putenv
