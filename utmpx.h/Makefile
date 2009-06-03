all:    t_utmpx_enum		\
	t_utmpx_pututxline	\

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_utmpx_enum: t_utmpx_enum.c
	$(CC) $(CCFLAGS) $(LIB) t_utmpx_enum.c -o t_utmpx_enum

t_utmpx_enum: t_utmpx_pututxline.c
	$(CC) $(CCFLAGS) $(LIB) t_utmpx_pututxline.c -o t_utmpx_pututxline


clean:
	git clean -f

run:
	@printf "t_utmpx_enum: "
	@-./t_utmpx_enum

	@printf "t_utmpx_pututxline: "
	@-./t_utmpx_pututxline
