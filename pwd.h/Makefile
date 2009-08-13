all:    t_pwd

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_pwd: t_pwd.c
	$(CC) $(CCFLAGS) $(LIB) t_pwd.c -o t_pwd

clean:
	git clean -f

run:
	@printf "t_pwd: "
	@-./t_pwd
