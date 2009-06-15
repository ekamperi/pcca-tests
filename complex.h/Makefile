all:	t_carg	\
	t_cimag \
	t_conj	\
	t_creal	\

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lm

t_carg: t_carg.c
	$(CC) $(CCFLAGS) $(LIB) t_carg.c -o t_carg

t_cimag: t_cimag.c
	$(CC) $(CCFLAGS) $(LIB) t_cimag.c -o t_cimag

t_cong: t_conj.c
	$(CC) $(CCFLAGS) $(LIB) t_conj.c -o t_conj

t_creal: t_creal.c
	$(CC) $(CCFLAGS) $(LIB) t_creal.c -o t_creal

clean:
	git clean -f

run:
	@printf "t_carg: "
	@-./t_carg

	@printf "t_cimag: "
	@-./t_cimag

	@printf "t_conj: "
	@-./t_conj

	@printf "t_creal: "
	@-./t_creal
