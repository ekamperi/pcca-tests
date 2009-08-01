all:    t_closedir	\
	t_dirent	\
	t_opendir	\
	t_readdir	\
	t_readdir_r

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_closedir: t_closedir.c
	$(CC) $(CCFLAGS) $(LIB) t_closedir.c -o t_closedir

t_dirent: t_dirent.c
	$(CC) $(CCFLAGS) $(LIB) t_dirent.c -o t_dirent

t_opendir: t_opendir.c
	$(CC) $(CCFLAGS) $(LIB) t_opendir.c -o t_opendir

t_readdir: t_readdir.c
	$(CC) $(CCFLAGS) $(LIB) t_readdir.c -o t_readdir

t_readdir_r: t_readdir_r.c
	$(CC) $(CCFLAGS) $(LIB) -lpthread t_readdir_r.c -o t_readdir_r

clean:
	git clean -f

run:
	@printf "t_closedir: "
	@-./t_closedir

	@printf "t_dirent: "
	@-./t_dirent

	@printf "t_opendir: "
	@-./t_opendir

	@printf "t_readdir: "
	@-./t_readdir

	@printf "t_readdir_r: "
	@-./t_readdir_r
