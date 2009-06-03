all:    t_closedir	\
	t_opendir	\

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_closedir: t_closedir.c
	$(CC) $(CCFLAGS) $(LIB) t_closedir.c -o t_closedir

t_opendir: t_opendir.c
	$(CC) $(CCFLAGS) $(LIB) t_opendir.c -o t_opendir

clean:
	git clean -f

run:
	@printf "t_closedir: "
	@-./t_closedir

	@printf "t_opendir: "
	@-./t_opendir
