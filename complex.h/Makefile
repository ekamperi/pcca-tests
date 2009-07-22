all:	t_cabs	\
	t_carg	\
	t_cacos	\
	t_cacosh	\
	t_casin	\
	t_casinh	\
	t_catan	\
	t_catanh	\
	t_ccos	\
	t_ccosh	\
	t_cexp	\
	t_cimag \
	t_clog	\
	t_conj	\
	t_complex	\
	t_cpow	\
	t_cproj	\
	t_creal	\
	t_csin	\
	t_csinh	\
	t_csqrt	\
	t_ctan	\
	t_ident	\
	t_imgconstant	\
	t_signbit

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g -std=c99
LIB=-lm

t_cabs: t_cabs.c
	$(CC) $(CCFLAGS) $(LIB) t_cabs.c -o t_cabs

t_carg: t_carg.c
	$(CC) $(CCFLAGS) $(LIB) t_carg.c -o t_carg

t_cacos: t_cacos.c
	$(CC) $(CCFLAGS) $(LIB) t_cacos.c -o t_cacos

t_cacosh: t_cacosh.c
	$(CC) $(CCFLAGS) $(LIB) t_cacosh.c -o t_cacosh

t_casin: t_casin.c
	$(CC) $(CCFLAGS) $(LIB) t_casin.c -o t_casin

t_casinh: t_casinh.c
	$(CC) $(CCFLAGS) $(LIB) t_casinh.c -o t_casinh

t_catan: t_catan.c
	$(CC) $(CCFLAGS) $(LIB) t_catan.c -o t_catan

t_catanh: t_catanh.c
	$(CC) $(CCFLAGS) $(LIB) t_catanh.c -o t_catanh

t_ccos:	t_ccos.c
	$(CC) $(CCFLAGS) $(LIB) t_ccos.c -o t_ccos

t_ccosh: t_ccosh.c
	$(CC) $(CCFLAGS) $(LIB) t_ccosh.c -o t_ccosh

t_cexp: t_cexp.c
	$(CC) $(CCFLAGS) $(LIB) t_cexp.c -o t_cexp

t_cimag: t_cimag.c
	$(CC) $(CCFLAGS) $(LIB) t_cimag.c -o t_cimag

t_clog: t_clog.c
	$(CC) $(CCFLAGS) $(LIB) t_clog.c -o t_clog

t_complex: t_complex.c
	$(CC) $(CCFLAGS) $(LIB) t_complex.c -o t_complex

t_conj: t_conj.c
	$(CC) $(CCFLAGS) $(LIB) t_conj.c -o t_conj

t_cpow: t_cpow.c
	$(CC) $(CCFLAGS) $(LIB) t_cpow.c -o t_cpow

t_cproj: t_cproj.c
	$(CC) $(CCFLAGS) $(LIB) t_cproj.c -o t_cproj

t_creal: t_creal.c
	$(CC) $(CCFLAGS) $(LIB) t_creal.c -o t_creal

t_csin: t_csin.c
	$(CC) $(CCFLAGS) $(LIB) t_csin.c -o t_csin

t_csinh: t_csinh.c
	$(CC) $(CCFLAGS) $(LIB) t_csinh.c -o t_csinh

t_csqrt: t_csqrt.c
	$(CC) $(CCFLAGS) $(LIB) t_csqrt.c -o t_csqrt

t_ctan: t_ctan.c
	$(CC) $(CCFLAGS) $(LIB) t_ctan.c -o t_ctan

t_ident: t_ident.c
	$(CC) $(CCFLAGS) $(LIB) t_ident.c -o t_ident

t_imgconstant: t_imgconstant.c
	$(CC) $(CCFLAGS) $(LIB) t_imgconstant.c -o t_imgconstant

t_signbit: t_signbit.c
	$(CC) $(CCFLAGS) $(LIB) t_signbit.c -o t_signbit

clean:
	git clean -f

run:
	@printf "t_cabs: "
	@-./t_cabs

	@printf "t_carg: "
	@-./t_carg

	@printf "t_cacos: "
	@-./t_cacos

	@printf "t_cacosh: "
	@-./t_cacosh

	@printf "t_casin: "
	@-./t_casin

	@printf "t_casinh: "
	@-./t_casinh

	@printf "t_catan: "
	@-./t_catan

	@printf "t_catanh: "
	@-./t_catanh

	@printf "t_ccos: "
	@-./t_ccos

	@printf "t_ccosh: "
	@./t_ccosh

	@printf "t_cexp: "
	@-./t_cexp

	@printf "t_cimag: "
	@-./t_cimag

	@printf "t_clog: "
	@-./t_clog

	@printf "t_complex: "
	@-./t_complex

	@printf "t_conj: "
	@-./t_conj

	@printf "t_cpow: "
	@-./t_cpow

	@printf "t_cproj: "
	@-./t_cproj

	@printf "t_creal: "
	@-./t_creal

	@printf "t_csin: "
	@-./t_csin

	@printf "t_csinh: "
	@-./t_csinh

	@printf "t_csqrt: "
	@-./t_csqrt

	@printf "t_ctan: "
	@-./t_ctan

	@printf "t_ident: "
	@-./t_ident

	@printf "t_imgconstant: "
	@-./t_imgconstant

	@printf "t_signbit: "
	@-./t_signbit
