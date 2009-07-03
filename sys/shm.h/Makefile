all:	t_shmid_ds

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_shmid_ds: t_shmid_ds.c
	$(CC) $(CCFLAGS) $(LIB) t_shmid_ds.c -o t_shmid_ds

clean:
	git clean -f

run:
	@printf "t_shmid_ds: "
	@-./t_shmid_ds
