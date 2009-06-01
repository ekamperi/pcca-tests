all:	t_fmax \
	t_fmaxf	\
	t_fmaxl	\
	t_fmin	\
	t_fminf	\
	t_fminl	\
	t_fdim	\
	t_fdimf	\
	t_fdiml

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lm

t_fmax: t_fmax.c
	$(CC) $(CCFLAGS) $(LIB) t_fmax.c -o t_fmax

t_fmaxf: t_fmaxf.c
	$(CC) $(CCFLAGS) $(LIB) t_fmaxf.c -o t_fmaxf

t_fmaxl: t_fmaxl.c
	$(CC) $(CCFLAGS) $(LIB) t_fmaxl.c -o t_fmaxl

t_fmin: t_fmin.c
	$(CC) $(CCFLAGS) $(LIB) t_fmin.c -o t_fmin

t_fminf: t_fminf.c
	$(CC) $(CCFLAGS) $(LIB) t_fmin.c -o t_fmin

t_fminl: t_fminl.c
	$(CC) $(CCFLAGS) $(LIB) t_fminl.c -o t_fminl

t_fdim: t_fdim.c
	$(CC) $(CCFLAGS) $(LIB) t_fdim.c -o t_fdim

t_fdimf: t_fdimf.c
	$(CC) $(CCFLAGS) $(LIB) t_fdimf.c -o t_fdimf

t_fdiml: t_fdiml.c
	$(CC) $(CCFLAGS) $(LIB) t_fdiml.c -o t_fdiml

clean:
	git clean -f

run:
	@printf "t_fmax........: "
	@-./t_fmax

	@printf "t_fmaxf.......: "
	@-./t_fmaxf

	@printf "t_fmaxl.......: "
	@-./t_fmaxl

	@printf "t_fmin........: "
	@-./t_fmin

	@printf "t_fminf.......: "
	@-./t_fminf

	@printf "t_fminl.......: "
	@-./t_fminl

	@printf "t_fdim........: "
	@-./t_fdim

	@printf "t_fdimf.......: "
	@-./t_fdimf

	@printf "t_fdiml.......: "
	@-./t_fdiml
