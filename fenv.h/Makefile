all:	t_fexcept	\
	t_fenv

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lm

t_fexcept: t_fexcept.c
	$(CC) $(CCFLAGS) $(LIB) t_fexcept.c -o t_fexcept

t_fenv: t_fenv.c
	$(CC) $(CCFLAGS) t_fenv.c -o t_fenv

clean:
	git clean -f

run:
	@printf "t_fexcept: "
	@-./t_fexcept

	@printf "t_fenv: "
	@-./t_fenv

