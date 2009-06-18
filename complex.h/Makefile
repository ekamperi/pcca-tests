all:	t_carg	\
	t_ccos	\
	t_cimag \
	t_conj	\
	t_creal	\
	t_csin	\
	t_ctan

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lm

t_carg: t_carg.c
	$(CC) $(CCFLAGS) $(LIB) t_carg.c -o t_carg

t_ccos:	t_ccos.c
	$(CC) $(CCFLAGS) $(LIB) t_ccos.c -o t_ccos

t_cimag: t_cimag.c
	$(CC) $(CCFLAGS) $(LIB) t_cimag.c -o t_cimag

t_conj: t_conj.c
	$(CC) $(CCFLAGS) $(LIB) t_conj.c -o t_conj

t_creal: t_creal.c
	$(CC) $(CCFLAGS) $(LIB) t_creal.c -o t_creal

t_csin: t_csin.c
	$(CC) $(CCFLAGS) $(LIB) t_csin.c -o t_csin

t_ctan: t_ctan.c
	$(CC) $(CCFLAGS) $(LIB) t_ctan.c -o t_ctan

clean:
	git clean -f

run:
	@printf "t_carg: "
	@-./t_carg

	@printf "t_ccos: "
	@-./t_ccos

	@printf "t_cimag: "
	@-./t_cimag

	@printf "t_conj: "
	@-./t_conj

	@printf "t_creal: "
	@-./t_creal

	@printf "t_csin: "
	@-./t_csin

	@printf "t_ctan: "
	@-./t_ctan
