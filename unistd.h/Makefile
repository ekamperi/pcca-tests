all:	t_access	\
	t_alarm		\
	t_chdir		\
	t_confstr	\
	t_fchdir	\
	t_getcwd	\
	t_getgroups	\
	t_gethostid	\
	t_gethostname	\
	t_getlogin	\
	t_getlogin_r	\
	t_getpgid	\
	t_getpgrp	\
	t_isatty	\
	t_lockf		\
	t_nice		\
	t_nice_thr	\
	t_pause		\
	t_pipe		\
	t_readlink	\
	t_ttyname	\
	t_tcsetpgrp	\
	t_unistd
#	t_ttyname_r

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_access: t_access.c
	$(CC) $(CCFLAGS) $(LIB) t_access.c -o t_access

t_alarm: t_alarm.c
	$(CC) $(CCFLAGS) $(LIB) t_alarm.c -o t_alarm

t_chdir: t_chdir.c
	$(CC) $(CCFLAGS) $(LIB) t_chdir.c -o t_chdir	

t_confstr: t_confstr.c
	$(CC) $(CCFLAGS) $(LIB) t_confstr.c -o t_confstr

t_fchdir: t_fchdir.c
	$(CC) $(CCFLAGS) $(LIB) t_fchdir.c -o t_fchdir

t_getcwd: t_getcwd.c
	$(CC) $(CCFLAGS) $(LIB) t_getcwd.c -o t_getcwd

t_getgroups: t_getgroups.c
	$(CC) $(CCFLAGS) $(LIB) t_getgroups.c -o t_getgroups

t_gethostid: t_gethostid.c
	$(CC) $(CCFLAGS) $(LIB) t_gethostid.c -o t_gethostid

t_gethostname: t_gethostname.c
	$(CC) $(CCFLAGS) $(LIB) t_gethostname.c -o t_gethostname

t_getlogin: t_getlogin.c
	$(CC) $(CCFLAGS) $(LIB) t_getlogin.c -o t_getlogin

t_getlogin_r: t_getlogin_r.c
	$(CC) $(CCFLAGS) $(LIB) t_getlogin_r.c -o t_getlogin_r

t_getpgid: t_getpgid.c
	$(CC) $(CCFLAGS) $(LIB) t_getpgid.c -o t_getpgid

t_getpgrp: t_getpgrp.c
	$(CC) $(CCFLAGS) $(LIB) t_getpgrp.c -o t_getpgrp

t_isatty: t_isatty.c
	$(CC) $(CCFLAGS) $(LIB) t_isatty.c -o t_isatty

t_lockf: t_lockf.c
	$(CC) $(CCFLAGS) $(LIB) t_lockf.c -o t_lockf

t_nice: t_nice.c
	$(CC) $(CCFLAGS) $(LIB) t_nice.c -o t_nice

t_nice_thr: t_nice_thr.c
	$(CC) $(CCFLAGS) $(LIB) -lpthread t_nice_thr.c -o t_nice_thr

t_pause: t_pause.c
	$(CC) $(CCFLAGS) $(LIB) t_pause.c -o t_pause

t_pipe: t_pipe.c
	$(CC) $(CCFLAGS) $(LIB) t_pipe.c -o t_pipe

t_readlink: t_readlink.c
	$(CC) $(CCFLAGS) $(LIB) t_readlink.c -o t_readlink

tcsetpgrp: t_tcsetpgrp.c
	$(CC) $(CCFLAGS) $(LIB) t_tcsetpgrp.c -o t_tcsetpgrp

t_ttyname: t_ttyname.c
	$(CC) $(CCFLAGS) $(LIB) t_ttyname.c -o t_ttyname

t_ttyname_r: t_ttyname_r.c
	$(CC) $(CCFLAGS) $(LIB) t_ttyname_r.c -o t_ttyname_r

t_unistd: t_unistd.c
	$(CC) $(CCFLAGS) $(LIB) t_unistd.c -o t_unistd

clean:
	git clean -f

run:
	@printf "t_access: "
	@-./t_access

	@printf "t_alarm: "
	@-./t_alarm

	@printf "t_chdir: "
	@-./t_chdir

	@printf "t_confstr: "
	@-./t_confstr

	@printf "t_fchdir: "
	@-./t_fchdir

	@printf "t_getcwd: "
	@-./t_getcwd

	@printf "t_getgroups: "
	@-./t_getgroups

	@printf "t_gethostid: "
	@-./t_gethostid

	@printf "t_gethostname: "
	@-./t_gethostname

	@printf "t_getlogin: "
	@-./t_getlogin

	@printf "t_getlogin_r: "
	@-./t_getlogin_r

	@printf "t_getpgid: "
	@-./t_getpgid

	@printf "t_isatty: "
	@-./t_isatty

	@printf "t_lockf: "
	@-./t_lockf

	@printf "t_nice: "
	@-./t_nice

	@printf "t_nice_thr: "
	@-./t_nice_thr

	@printf "t_pause: "
	@-./t_pause

	@printf "t_pipe: "
	@-./t_pipe

	@printf "t_readlink: "
	@-./t_readlink

	@printf "t_tcsetpgrp: "
	@-./t_tcsetpgrp

	@printf "t_ttyname: "
	@-./t_ttyname

#	@printf "t_ttyname_r: "
#	@-./t_ttyname_r

	@printf "t_unistd: "
	@-./t_unistd
