all:    t_fnmatch	\
	t_fnmatch2

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_fnmatch: t_fnmatch.c
	$(CC) $(CCFLAGS) $(LIB) t_fnmatch.c -o t_fnmatch

t_fnmatch2: t_fnmatch2.c
	$(CC) $(CCFLAGS) $(LIB) t_fnmatch2.c -o t_fnmatch2

clean:
	git clean -f

run:
	@printf "t_fnmatch: "
	@-./t_fnmatch

	@printf "t_fnmatch2: "
	@-./t_fnmatch2
