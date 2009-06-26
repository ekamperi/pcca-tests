#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <time.h>
#include <unistd.h>
#include <getopt.h>

int sleeping = 0; /* Number of sleeping (S) threads. */
int awake = 0;    /* Number of awake (A) threads. */
int p = 0;        /* Period (msec) after which A awakes S. */
int t = 0;        /* Number of threads, A awakes upon one single fire. */

int spurious = 0; /* Number of spurious wakeups. */
int valid = 0;	  /* Number of non spurious wakeups. */

pthread_mutex_t mtx_spurious = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_valid = PTHREAD_MUTEX_INITIALIZER;

struct slelm {
	pthread_t sl_tid;
	pthread_cond_t sl_cond;
	int sl_pred;
	int sl_id;
};

struct awelm {
	pthread_t aw_tid;
	int aw_id;
};

struct slelm *slpool;   /* Pool with sleeping threads. */
struct awelm *awpool;   /* Pool with awake threads. */

/* Function prototypes. */
static void *slthread(void *arg);
static void *awthread(void *arg);
static void dieu(const char *pname);

int main(int argc, char *argv[])
{
	int i, opt;

	/* Parse arguments. */
	while ((opt = getopt(argc, argv, "s:a:p:t:")) != -1) {
		switch (opt) {
		case 's':
			sleeping = atoi(optarg);
			break;
		case 'a':
			awake = atoi(optarg);
			break;
		case 'p':
			p = atoi(optarg);
			break;
		case 't':
			t = atoi(optarg);
			break;
		default:	/* '?' */
			dieu(argv[0]);
			/* Never reached. */
		}
	}

	/* optind is the argv[] index of the first non-option element. */
	if (optind < argc) {
		fprintf(stderr, "non-option argv[]-elements: ");
		while (optind < argc)
			fprintf(stderr, "%s ", argv[optind++]);
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}

	/* Make sure all arguments were supplied. */
	if (sleeping == 0 || awake == 0 || p == 0 || t == 0) {
		dieu(argv[0]);
		/* Never reached. */
	}

	/* XXX: slpool. */
	slpool = malloc(sleeping * sizeof(struct slelm));
	assert(slpool != NULL);
	for (i = 0; i < sleeping; i++) {
		assert(pthread_cond_init(&slpool[i].sl_cond, NULL) == 0);
		slpool[i].sl_pred = 0;
		slpool[i].sl_id = i;
		assert(pthread_create(&slpool[i].sl_tid, NULL, slthread,
			   (void *)&slpool[i]) == 0);
	}

	/* XXX: awpool. */
	awpool = malloc(awake * sizeof(struct awelm));
	assert(awpool != NULL);
	for (i = 0; i < awake; i++) {
		awpool[i].aw_id = i;
		assert(pthread_create(&awpool[i].aw_tid, NULL, awthread,
			   (void *)&awpool[i]) == 0);
	};

	/* Initialize random number generator. */
	srand(time(NULL));

	/* Wait for threads to complete. */
	for (i = 0; i < awake; i++)
		assert(pthread_join(awpool[i].aw_tid, NULL) == 0);

	/* Wake up still sleeping threads. */
	for (i = 0; i < sleeping; i++) {
		if (slpool[i].sl_pred == 0) {
			slpool[i].sl_pred = 1;
			assert(pthread_cond_signal(&slpool[i].sl_cond) == 0);
		}
	}

	/* Wait for threads to complete. */
	for (i = 0; i < sleeping; i++) {
		pthread_join(slpool[i].sl_tid, NULL);
		assert(pthread_cond_destroy(&slpool[i].sl_cond) == 0);
	}

	free(slpool);
	free(awpool);

	printf("spurious = %d\tvalid = %d\n", spurious, valid);

	return (EXIT_SUCCESS);
}

static void *
slthread(void *arg)
{
	pthread_mutex_t mtx;
	struct slelm *se;

	/*
	 * Retrieve our argument, but don't be tempted to dereference it,
	 * as this will result in pthread_{t, cond_t} objects being copied.
	 * The action of pthread*() functions on copies of initialized pthread*
	 * objects is undefined.
	 */
	se = (struct slelm *)arg;

	/* Initialize mutex. */
	assert(pthread_mutex_init(&mtx, NULL) == 0);

	/* This will block us. */
	for(;;) {
		assert(pthread_mutex_lock(&mtx) == 0);
		assert(pthread_cond_wait(&se->sl_cond, &mtx) == 0);
		assert(pthread_mutex_unlock(&mtx) == 0);
		if (se->sl_pred == 1) {
			assert(pthread_mutex_lock(&mtx_valid) == 0);
			valid++;
			assert(pthread_mutex_unlock(&mtx_valid) == 0);
			break;
		}
		assert(pthread_mutex_lock(&mtx_spurious) == 0);
		spurious++;
		assert(pthread_mutex_lock(&mtx_spurious) == 0);
	}

	/* Destroy mutex. */
	assert(pthread_mutex_destroy(&mtx) == 0);

	pthread_exit(NULL);
}

static void *
awthread(void *arg)
{
	struct awelm *ae;
	struct timespec ts;
	int i, j;

	/*
	 * Retrieve our argument, but don't be tempted to dereference it,
	 * as this will result in pthread_{t, cond_t} objects being copied.
	 * The action of pthread*() functions on copies of initialized pthread*
	 * objects is undefined.
	 */
	ae = (struct awelm *)arg;

	/* Sleep. */
	ts.tv_sec = p / 1000;		/* p is in msec. */
	ts.tv_nsec = 1000000 * (p - 1000*ts.tv_sec);
	assert(nanosleep(&ts, NULL) == 0);

	/* We awake `t' random threads. */
	for (i = 0; i < t; i++) {
		j = ae->aw_id * (sleeping/awake) + rand() % (sleeping/awake);
		slpool[j].sl_pred = 1;
		assert(pthread_cond_signal(&slpool[j].sl_cond) == 0);
	}

	pthread_exit(NULL);
}

static void
dieu(const char *pname)
{
	fprintf(stderr,
	    "Usage: %s -s threads -a threads -p frequency -t target\n", pname);
	exit(EXIT_FAILURE);
}
