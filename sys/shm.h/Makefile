all:	t_shm	\
	t_shmat	\

CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_shm: t_shm.c
	$(CC99) $(CCFLAGS) $(LIB) t_shm.c -o t_shm

t_shmat: t_shmat.c
	$(CC99) $(CCFLAGS) $(LIB) t_shmat.c -o t_shmat

clean:
	git clean -f

run:
	@printf "t_shm: "
	@-./t_shm

	@printf "t_shmat: "
	@-./t_shmat
