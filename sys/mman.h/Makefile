all:	t_mlockall	\
	t_mmap		\
	t_mmap_errno	\
	t_shm

CC=gcc
CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lrt

t_mlockall: t_mlockall.c
	$(CC) $(CCFLAGS) t_mlockall.c -o t_mlockall

t_mmap: t_mmap.c
	$(CC99) $(CCFLAGS) $(LIB) t_mmap.c -o t_mmap

t_mmap_errno: t_mmap_errno.c
	$(CC99) $(CCFLAGS) $(LIB) t_mmap_errno.c -o t_mmap_errno

t_shm: t_shm.c
	$(CC) $(CCFLAGS) $(LIB) t_shm.c -o t_shm

clean:
	git clean -f

run:
	@printf "t_mlockall: "
	@-./t_mlockall

	@printf "t_mmap: "
	@-./t_mmap

	@printf "t_mmap_errno: "
	@-./t_mmap_errno

	@printf "t_shm: "
	@-./t_shm
