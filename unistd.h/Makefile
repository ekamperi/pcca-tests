all:	t_access	\
	t_access2	\
	t_alarm		\
	t_chdir		\
	t_confstr	\
	t_fchdir	\
	t_fchdir_suid	\
	t_fork_buf	\
	t_fork_signal	\
	t_getcwd	\
	t_getgroups	\
	t_gethostid	\
	t_gethostname	\
	t_getlogin	\
	t_getlogin_r	\
	t_getpgid	\
	t_getpgrp	\
	t_getpid	\
	t_getppid	\
	t_getsid	\
	t_getuid	\
	t_isatty	\
	t_link		\
	t_lockf		\
	t_lockf2	\
	t_nice		\
	t_nice_thr	\
	t_pause		\
	t_pipe		\
	t_pipe_fork	\
	t_pipe_thr	\
	t_readlink	\
	t_setregid	\
	t_setregid_sgid	\
	t_ttyname	\
	t_tcsetpgrp	\
	t_unistd
#	t_ttyname_r

CC=gcc
CC99=gcc -std=c99
CCFLAGS=-Wall -W -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g

t_access: t_access.c
	$(CC) $(CCFLAGS) t_access.c -o t_access

t_access2: t_access2.c
	$(CC) $(CCFLAGS) t_access2.c -o t_access2
	sudo chown root ./t_access2
	sudo chmod u+s ./t_access2   # set setuid bit

t_alarm: t_alarm.c
	$(CC) $(CCFLAGS) t_alarm.c -o t_alarm

t_chdir: t_chdir.c
	$(CC) $(CCFLAGS) t_chdir.c -o t_chdir	

t_confstr: t_confstr.c
	$(CC99) $(CCFLAGS) t_confstr.c -o t_confstr

t_fchdir: t_fchdir.c
	$(CC) $(CCFLAGS) t_fchdir.c -o t_fchdir

t_fchdir_suid: t_fchdir_suid.c
	$(CC) $(CCFLAGS) t_fchdir_suid.c -o t_fchdir_suid
	sudo chown root ./t_fchdir_suid
	sudo chmod u+s ./t_fchdir_suid	# set setuid bit

t_fork_buf: t_fork_buf.c
	$(CC) $(CCFLAGS) t_fork_buf.c -o t_fork_buf	

t_fork_signal: t_fork_signal.c
	$(CC) $(CCFLAGS) t_fork_signal.c -o t_fork_signal

t_getcwd: t_getcwd.c
	$(CC) $(CCFLAGS) t_getcwd.c -o t_getcwd

t_getgroups: t_getgroups.c
	$(CC) $(CCFLAGS) t_getgroups.c -o t_getgroups

t_gethostid: t_gethostid.c
	$(CC99) $(CCFLAGS) t_gethostid.c -o t_gethostid

t_gethostname: t_gethostname.c
	$(CC) $(CCFLAGS) t_gethostname.c -o t_gethostname

t_getlogin: t_getlogin.c
	$(CC) $(CCFLAGS) t_getlogin.c -o t_getlogin

t_getlogin_r: t_getlogin_r.c
	$(CC) $(CCFLAGS) t_getlogin_r.c -o t_getlogin_r

t_getpgid: t_getpgid.c
	$(CC99) $(CCFLAGS) t_getpgid.c -o t_getpgid

t_getpgrp: t_getpgrp.c
	$(CC) $(CCFLAGS) t_getpgrp.c -o t_getpgrp

t_getpid: t_getpid.c
	$(CC) $(CCFLAGS) t_getpid.c -o t_getpid

t_getppid: t_getppid.c
	$(CC) $(CCFLAGS) t_getppid.c -o t_getppid

t_getuid: t_getuid.c
	$(CC) $(CCFLAGS) t_getuid.c -o t_getuid

t_isatty: t_isatty.c
	$(CC) $(CCFLAGS) t_isatty.c -o t_isatty

t_link: t_link.c
	$(CC) $(CCFLAGS) t_link.c -o t_link

t_lockf: t_lockf.c
	$(CC99) $(CCFLAGS) t_lockf.c -o t_lockf

t_lockf2: t_lockf2.c
	$(CC99) $(CCFLAGS) t_lockf2.c -o t_lockf2

t_nice: t_nice.c
	$(CC99) $(CCFLAGS) t_nice.c -o t_nice

t_nice_thr: t_nice_thr.c
	$(CC) $(CCFLAGS) -lpthread t_nice_thr.c -o t_nice_thr

t_pause: t_pause.c
	$(CC) $(CCFLAGS) t_pause.c -o t_pause

t_pipe: t_pipe.c
	$(CC) $(CCFLAGS) t_pipe.c -o t_pipe

t_pipe_fork: t_pipe_fork.c
	$(CC) $(CCFLAGS) t_pipe_fork.c -o t_pipe_fork -lcrypto

t_pipe_thr: t_pipe_thr.c
	$(CC) $(CCFLAGS) t_pipe_thr.c -o t_pipe_thr -lcrypto -pthread

t_readlink: t_readlink.c
	$(CC) $(CCFLAGS) t_readlink.c -o t_readlink

t_setregid: t_setregid.c
	$(CC) $(CCFLAGS) t_setregid.c -o t_setregid

t_setregid_sgid: t_setregid_sgid.c
	$(CC99) $(CCLFAGA) t_setregid_sgid.c -o t_setregid_sgid
	sudo chgrp root ./t_setregid_sgid
	sudo chmod g+s ./t_setregid_sgid

tcsetpgrp: t_tcsetpgrp.c
	$(CC) $(CCFLAGS) t_tcsetpgrp.c -o t_tcsetpgrp

t_getsid: t_getsid.c
	$(CC99) $(CCFLAGS) t_getsid.c -o t_getsid

t_ttyname: t_ttyname.c
	$(CC) $(CCFLAGS) t_ttyname.c -o t_ttyname

t_ttyname_r: t_ttyname_r.c
	$(CC) $(CCFLAGS) t_ttyname_r.c -o t_ttyname_r

t_unistd: t_unistd.c
	$(CC) $(CCFLAGS) t_unistd.c -o t_unistd

clean:
	git clean -f

run:
	@printf "t_access: "
	@-./t_access

	@printf "t_access2: "
	@-./t_access2

	@printf "t_alarm: "
	@-./t_alarm

	@printf "t_chdir: "
	@-./t_chdir

	@printf "t_confstr: "
	@-./t_confstr

	@printf "t_fchdir: "
	@-./t_fchdir

	@printf "t_fchdir_suid: "
	@-./t_fchdir_suid

	@printf "t_fork_buf: "
	@-./t_fork_buf

	@printf "t_fork_signal: "
	@-./t_fork_signal

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

	@printf "t_getpid: "
	@-./t_getpid

	@printf "t_getppid: "
	@-./t_getppid

	@printf "t_getsid: "
	@-./t_getsid

	@printf "t_getuid: "
	@-./t_getuid

	@printf "t_isatty: "
	@-./t_isatty

	@printf "t_link: "
	@-./t_link

	@printf "t_lockf: "
	@-./t_lockf

	@printf "t_lockf2: "
	@-./t_lockf2

	@printf "t_nice: "
	@-./t_nice

	@printf "t_nice_thr: "
	@-./t_nice_thr

	@printf "t_pause: "
	@-./t_pause

	@printf "t_pipe: "
	@-./t_pipe

	@printf "t_pipe_fork: "
	@-./t_pipe_fork

	@printf "t_pipe_thr: "
	@-./t_pipe_thr

	@printf "t_readlink: "
	@-./t_readlink

	@printf "t_tcsetpgrp: "
	@-./t_tcsetpgrp

	@printf "t_setregid: "
	@-./t_setregid

	@printf "t_setregid_sgid: "
	@-./t_setregid_sgid

	@printf "t_ttyname: "
	@-./t_ttyname

#	@printf "t_ttyname_r: "
#	@-./t_ttyname_r

	@printf "t_unistd: "
	@-./t_unistd
