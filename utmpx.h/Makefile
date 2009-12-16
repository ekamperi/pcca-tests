all:	t_utmpx			\
	t_utmpx_enum		\
	t_utmpx_pututxline	\

CC=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_utmpx: t_utmpx.c
	$(CC) $(CCFLAGS) t_utmpx.c -o t_utmpx

t_utmpx_enum: t_utmpx_enum.c
	$(CC) $(CCFLAGS) t_utmpx_enum.c -o t_utmpx_enum

t_utmpx_pututxline: t_utmpx_pututxline.c
	$(CC) $(CCFLAGS) t_utmpx_pututxline.c -o t_utmpx_pututxline
	sudo chown root ./t_utmpx_pututxline
	sudo chmod u+s ./t_utmpx_pututxline   # set setuid bit

clean:
	git clean -f

run:
	@printf "t_utmpx: "
	@-./t_utmpx

	@printf "t_utmpx_enum: "
	@-./t_utmpx_enum

	@printf "t_utmpx_pututxline: "
	@-./t_utmpx_pututxline
