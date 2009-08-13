all:	t_lfind	\
	t_lsearch	\
	t_hsearch	\
	t_tsearch

CC=gcc
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_lfind: t_lfind.c
	$(CC) $(CCFLAGS) $(LIB) t_lfind.c -o t_lfind

t_lsearch: t_lsearch.c
	$(CC) $(CCFLAGS) $(LIB) t_lsearch.c -o t_lsearch

t_hsearch: t_hsearch.c
	$(CC) $(CCFLAGS) $(LIB) t_hsearch.c -o t_hsearch

t_tsearch: t_tsearch.c
	$(CC) $(CCFLAGS) $(LIB) t_tsearch.c -o t_tsearch

clean:
	git clean -f

run:
	@printf "t_lfind: "
	@-./t_lfind

	@printf "t_lsearch: "
	@-./t_lsearch

	@printf "t_hsearch: "
	@-./t_hsearch

	@printf "t_tsearch: "
	@-./t_tsearch
