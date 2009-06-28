all:	t_pthread_attr_getguardsize		\
	t_pthread_attr_getstacksize		\
	t_pthread_barrier_init			\
	t_pthread_barrier_wait			\
	t_pthread_barrierattr_getpshared	\
	t_pthread_barrierattr_init		\
	t_pthread_cond_init			\
	t_pthread_cond_wait			\
	t_pthread_rwlock			\
	t_pthread_rwlock_init			\
	t_pthread_rwlock_deadlock		\
	t_pthread_rwlock_timedrdlock		\
	t_pthread_rwlock_timedwrlock		\
	t_pthread_rwlock_trywrlock		\
	t_pthread_setcancelstate		\
	t_pthread_setcanceltype			\
	t_pthread_testcancel

CC=gcc
CCFLAGS=-Wall -W -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes \
	-Wmissing-declarations -Winline -Wundef -Wnested-externs -Wcast-qual \
	-Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal \
	-Wswitch -Wbad-function-cast -g
LIB=-lthread_xu

t_pthread_attr_getguardsize: t_pthread_attr_getguardsize.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_attr_getguardsize.c -o t_pthread_attr_getguardsize

t_pthread_attr_getstacksize: t_pthread_attr_getstacksize.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_attr_getstacksize.c -o t_pthread_attr_getstacksize

t_pthread_barrier_init: t_pthread_barrier_init.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_barrier_init.c -o t_pthread_barrier_init

t_pthread_barrier_wait: t_pthread_barrier_wait.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_barrier_wait.c -o t_pthread_barrier_wait

t_pthread_barrierattr_getpshared: t_pthread_barrierattr_getpshared.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_barrierattr_getpshared.c -o t_pthread_barrierattr_getpshared

t_pthread_barrierattr_init: t_pthread_barrierattr_init.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_barrierattr_init.c -o t_pthread_barrierattr_init

t_pthread_cond_init: t_pthread_cond_init.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_cond_init.c -o t_pthread_cond_init

t_pthread_cond_wait: t_pthread_cond_wait.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_cond_wait.c -o t_pthread_cond_wait

t_pthread_rwlock: t_pthread_rwlock.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_rwlock.c -o t_pthread_rwlock

t_pthread_rwlock_init: t_pthread_rwlock_init.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_rwlock_init.c -o t_pthread_rwlock_init

t_pthread_rwlock_deadlock: t_pthread_rwlock_deadlock.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_rwlock_deadlock.c -o t_pthread_rwlock_deadlock

t_pthread_rwlock_timedrdlock: t_pthread_rwlock_timedrdlock.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_rwlock_timedrdlock.c -o t_pthread_rwlock_timedrdlock

t_pthread_rwlock_timedwrlock: t_pthread_rwlock_timedwrlock.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_rwlock_timedwrlock.c -o t_pthread_rwlock_timedwrlock

t_pthread_rwlock_trywrlock: t_pthread_rwlock_trywrlock.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_rwlock_trywrlock.c -o t_pthread_rwlock_trywrlock

t_pthread_setcancelstate: t_pthread_setcancelstate.c
	$(CC) $(CCFLAGS) $(LIB)  t_pthread_setcancelstate.c -o t_pthread_setcancelstate

t_pthread_setcanceltype: t_pthread_setcanceltype.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_setcanceltype.c -o t_pthread_setcanceltype

t_pthread_testcancel: t_pthread_testcancel.c
	$(CC) $(CCFLAGS) $(LIB) t_pthread_testcancel.c -o t_pthread_testcancel

clean:
	git clean -f

run:
	@printf "t_pthread_attr_getguardsize: "
	@-./t_pthread_attr_getguardsize

	@printf "t_pthread_attr_getstacksize: "
	@-./t_pthread_attr_getstacksize

	@printf "t_pthread_barrier_init: "
	@-./t_pthread_barrier_init

	@printf "t_pthread_barrier_wait: "
	@-./t_pthread_barrier_wait

	@printf "t_pthread_barrierattr_getpshared: "
	@-./t_pthread_barrierattr_getpshared

	@printf "t_pthread_barrierattr_init: "
	@-./t_pthread_barrierattr_init

	@printf "t_pthread_cond_init: "
	@-./t_pthread_cond_init

	@printf "t_pthread_cond_wait: "
	@-./t_pthread_cond_wait

	@printf "t_pthread_rwlock: "
	@-./t_pthread_rwlock

	@printf "t_pthread_rwlock_init: "
	@-./t_pthread_rwlock_init

	@printf "t_pthread_rwlock_deadlock: "
	@-./t_pthread_rwlock_deadlock

	@printf "t_pthread_rwlock_timedrdlock: "
	@-./t_pthread_rwlock_timedrdlock

	@printf "t_pthread_rwlock_timedwrlock: "
	@-./t_pthread_rwlock_timedwrlock

	@printf "t_pthread_rwlock_trywrlock: "
	@-./t_pthread_rwlock_trywrlock

	@printf "t_pthread_setcancelstate: "
	@./t_pthread_setcancelstate

	@printf "t_pthread_setcanceltype: "
	@./t_pthread_setcanceltype
