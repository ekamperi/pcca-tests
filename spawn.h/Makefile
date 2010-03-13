all:	t_posix_spawn

CC=gcc
CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_posix_spawn: t_posix_spawn.c
	$(CC) $(CCFLAGS) $(LIB) t_posix_spawn.c -o t_posix_spawn

clean:
	git clean -f

run:
	@printf "t_posix_spawn: "
	@-./t_posix_spawn
