all:	t_posix_memalign	\
	t_posix_openpt		\
	t_putenv		\
	t_qsort			\
	t_realpath		\
	t_stdlib		\
	t_strtod		\

CC=gcc
CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=

t_posix_memalign: t_posix_memalign.c
	$(CC) $(CCFLAGS) $(LIB) t_posix_memalign.c -o t_posix_memalign

t_posix_openpt: t_posix_openpt.c
	$(CC99) $(CCFLAGS) $(LIB) t_posix_openpt.c -o t_posix_openpt

t_putenv: t_putenv.c
	$(CC) $(CCFLAGS) $(LIB) t_putenv.c -o t_putenv

t_qsort: t_qsort.c
	$(CC) $(CCFLAGS) -lpthread t_qsort.c -o t_qsort

t_realpath: t_realpath.c
	$(CC) $(CCFLAGS) t_realpath.c -o t_realpath

t_stdlib: t_stdlib.c
	$(CC) $(CCFLAGS) $(LIB) t_stdlib.c -o t_stdlib

t_strtod: t_strtod.c
	$(CC) $(CCFLAGS) t_strtod.c -o t_strtod

clean:
	git clean -f

run:
	@printf "t_posix_memalign: "
	@-./t_posix_memalign

	@printf "t_posix_openpt: "
	@-./t_posix_openpt

	@printf "t_putenv: "
	@-./t_putenv

	@printf "t_qsort: "
	@-./t_qsort

	@printf "t_realpath: "
	@-./t_realpath

	@printf "t_stdlib: "
	@-./t_stdlib

	@printf "t_strtod: "
	@-./t_strtod
