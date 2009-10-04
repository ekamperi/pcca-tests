all:	t_dlsym

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_dlsym: t_dlsym.c
	$(CC) $(CCFLAGS) $(LIB) t_dlsym.c -o t_dlsym

clean:
	git clean -f

run:
	@printf "t_dlsym: "
	@-./t_dlsym
