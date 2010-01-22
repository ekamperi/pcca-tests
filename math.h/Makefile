all:	t_fmax		\
	t_fmaxf		\
	t_fmaxl		\
	t_fmin		\
	t_fminf		\
	t_fminl		\
	t_fdim		\
	t_fdimf		\
	t_fdiml 	\
	t_tgamma	\
	t_generr	\
	t_log		\
	t_nearbyint	\
	t_rint		\
	t_sin		\
	t_trig_ident

CC=gcc
CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
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
	$(CC) $(CCFLAGS) $(LIB) t_fmin.c -o t_fminf

t_fminl: t_fminl.c
	$(CC) $(CCFLAGS) $(LIB) t_fminl.c -o t_fminl

t_fdim: t_fdim.c
	$(CC99) $(CCFLAGS) $(LIB) t_fdim.c -o t_fdim

t_fdimf: t_fdimf.c
	$(CC99) $(CCFLAGS) $(LIB) t_fdimf.c -o t_fdimf

t_fdiml: t_fdiml.c
	$(CC99) $(CCFLAGS) $(LIB) t_fdiml.c -o t_fdiml

t_tgamma: t_tgamma.c
	$(CC99) $(CCFLAGS) $(LIB) t_tgamma.c -o t_tgamma

t_generr: t_generr.c
	$(CC) $(CCFLAGS) $(LIB) t_generr.c -o t_generr

t_log: t_log.c
	$(CC99) $(CCFLAGS) $(LIB) t_log.c -o t_log

t_nearbyint: t_nearbyint.c
	$(CC99) $(CCFLAGS) $(LIB) t_nearbyint.c -o t_nearbyint

t_rint: t_rint.c
	$(CC) $(CCFLAGS) $(LIB) t_rint.c -o t_rint

t_sin: t_sin.c
	$(CC) $(CCFLAGS) $(LIB) t_sin.c -o t_sin

t_trig_ident: t_trig_ident.c
	$(CC) $(CCFLAGS) $(LIB) t_trig_ident.c -o t_trig_ident

clean:
	git clean -f

run:
	@printf "t_fmax: "
	@-./t_fmax

	@printf "t_fmaxf: "
	@-./t_fmaxf

	@printf "t_fmaxl: "
	@-./t_fmaxl

	@printf "t_fmin: "
	@-./t_fmin

	@printf "t_fminf: "
	@-./t_fminf

	@printf "t_fminl: "
	@-./t_fminl

	@printf "t_fdim: "
	@-./t_fdim

	@printf "t_fdimf: "
	@-./t_fdimf

	@printf "t_fdiml: "
	@-./t_fdiml

	@printf "t_tgamma: "
	@-./t_tgamma

	@printf "t_generr: "
	@-./t_generr

	@printf "t_log: "
	@-./t_log

	@printf "t_rint: "
	@-./t_rint

	@printf "t_sin: "
	@-./t_sin

	@printf "t_trig_ident: "
	@-./t_trig_ident
