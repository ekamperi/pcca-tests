#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct scentry {
	const char *sc_desc;
	int sc_name;
} sctable[] = {
#ifdef	_SC_ASYNCHRONOUS_IO
	{ "_SC_ASYNCHRONOUS_IO", _SC_ASYNCHRONOUS_IO},
#endif
#ifdef	_SC_MAPPED_FILES
	{ "_SC_MAPPED_FILES",		_SC_MAPPED_FILES	},
#endif
#ifdef	_SC_MEMLOCK
	{ "_SC_MEMLOCK",		_SC_MEMLOCK		},
#endif
#ifdef	_SC_MEMLOCK_RANGE
	{ "_SC_MEMLOCK_RANGE",		_SC_MEMLOCK_RANGE	},
#endif
#ifdef	_SC_MEMORY_PROTECTION
	{ "_SC_MEMORY_PROTECTION",	_SC_MEMORY_PROTECTION	},
#endif
#ifdef	_SC_MESSAGE_PASSING
	{ "_SC_MESSAGE_PASSING",	_SC_MESSAGE_PASSING	},
#endif
#ifdef	_SC_PRIORITIZED_IO
	{ "_SC_PRIORITIZED_IO",		_SC_PRIORITIZED_IO	},
#endif
#ifdef	_SC_PRIORITY_SCHEDULING
	{ "_SC_PRIORITY_SCHEDULING",	_SC_PRIORITY_SCHEDULING	},
#endif
#ifdef	_SC_REALTIME_SIGNALS
	{ "_SC_REALTIME_SIGNALS",	_SC_REALTIME_SIGNALS	},
#endif
#ifdef	_SC_SEMAPHORES
	{ "_SC_SEMAPHORES",		_SC_SEMAPHORES		},
#endif
#ifdef	_SC_FSYNC
	{ "_SC_FSYNC",			_SC_FSYNC		},
#endif
#ifdef	_SC_SHARED_MEMORY_OBJECTS	
	{ "_SC_SHARED_MEMORY_OBJECTS",	_SC_SHARED_MEMORY_OBJECTS},
#endif
#ifdef	_SC_SYNCHRONIZED_IO
	{ "_SC_SYNCHRONIZED_IO",	_SC_SYNCHRONIZED_IO	},
#endif
#ifdef	_SC_TIMERS
	{ "_SC_TIMERS",			_SC_TIMERS		},
#endif
#ifdef	_SC_AIO_LISTIO_MAX
	{ "_SC_AIO_LISTIO_MAX",		_SC_AIO_LISTIO_MAX	},
#endif
#ifdef	_SC_AIO_MAX
	{ "_SC_AIO_MAX",		_SC_AIO_MAX		},
#endif
#ifdef	_SC_AIO_PRIO_DELTA_MAX
	{ "_SC_AIO_PRIO_DELTA_MAX",	_SC_AIO_PRIO_DELTA_MAX	},
#endif
#ifdef	_SC_DELAYTIMER_MAX
	{ "_SC_DELAYTIMER_MAX",		_SC_DELAYTIMER_MAX	},
#endif
#ifdef	_SC_MQ_OPEN_MAX
	{ "_SC_MQ_OPEN_MAX",		_SC_MQ_OPEN_MAX		},
#endif
#ifdef	_SC_PAGESIZE
	{ "_SC_PAGESIZE",		_SC_PAGESIZE		},
#endif
#ifdef	_SC_RTSIG_MAX
	{ "_SC_RTSIG_MAX",		_SC_RTSIG_MAX		},
#endif
#ifdef	_SC_SEM_NSEMS_MAX
	{ "_SC_SEM_NSEMS_MAX",		_SC_SEM_NSEMS_MAX	},
#endif
#ifdef	_SC_SEM_VALUE_MAX
	{ "_SC_SEM_VALUE_MAX",		_SC_SEM_VALUE_MAX	},
#endif
#ifdef	_SC_SIGQUEUE_MAX
	{ "_SC_SIGQUEUE_MAX",		_SC_SIGQUEUE_MAX	},
#endif
#ifdef	_SC_TIMER_MAX
	{ "_SC_TIMER_MAX",		_SC_TIMER_MAX		},
#endif
	{ NULL,				-1			}
};

int main(void)
{
	const struct scentry *sce;
	long rv;

	for (sce = sctable; sce != NULL; sce++) {
		if (sce->sc_desc == NULL && sce->sc_name == -1)
			break;

		errno = 0;
		rv = sysconf(sce->sc_name);
		printf("desc: %-20s\tvalue: %-10ld", sce->sc_desc, rv);
		if (rv == -1) {
			if (errno == 0)
				printf("\t[NOT SUPPORTED]");
			else
				printf("\t[INVALID      ]");
		} else {
			printf("\t+SUPPORTED+");
		}

		printf("\n");
	}
	
	return (EXIT_SUCCESS);
}
