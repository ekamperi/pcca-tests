all:	t_basename	\
	t_dirname	\

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_basename: t_basename.c
	$(CC) $(CCFLAGS) $(LIB) t_basename.c -o t_basename

t_dirname: t_dirname.c
	$(CC) $(CCFLAGS) $(LIB) t_dirname.c -o t_dirname

clean:
	git clean -f

run:
	@printf "t_basename: "
	@-./t_basename

	@printf "t_dirname: "
	@-./t_dirname
