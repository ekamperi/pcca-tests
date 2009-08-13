all:    t_msg

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_msg: t_msg.c
	$(CC) $(CCFLAGS) $(LIB) t_msg.c -o t_msg

clean:
	git clean -f

run:
	@printf "t_msg: "
	@-./t_msg
