#define _POSIX_SOURCE
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

#define UNUSED(var) ((void)(var))

#if 0
pthread_t test_thread;

void *thread_test_run (void *v)
{
	int i = 0;

	printf("%s: +\n", __func__);

	while (1) {
		printf("into thread %d\n", ++i);
		sleep(1);
	}

	printf("%s: -\n", __func__);

	return NULL;
}

int main(void)
{
	printf("%s: +\n", __func__);

	pthread_create(&test_thread, NULL, &thread_test_run, NULL);
	sleep(3);

	printf("%s: cancelling thread\n", __func__);
	pthread_cancel(test_thread);

	printf("%s: -\n", __func__);

	return 0;
}
#endif

#if 0
#define handle_error_en(en, msg) \
	do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static void *thread_func(void *ignored_argument)
{
	int s;

	/*
	 * Disable cancellation for a while, so that we don't immediately
	 * react to a cancellation request
	 */
	s = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	if (s)
		handle_error_en(s, "pthread_setcancelstate");

	printf("thread_func(): started; cancellation disabled\n");
	sleep(1);
	printf("thread_func(): about to enable cancellation\n");

	s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	if (s)
		handle_error_en(s, "pthread_setcancelstate");

	/* sleep() is a cancellation point */
	sleep(1000);

	/* Should never get here */
	printf("thread_func(): not canceled!\n");

	return NULL;
}

int main(void)
{
	int s;
	void *res;
	pthread_t thr;

	/* Start a thread and then send it a cancellation request */
	s = pthread_create(&thr, NULL, &thread_func, NULL);
	if (s)
		handle_error_en(s, "pthread_create");

	sleep(2);

	printf("main(): sending cancellation request\n");
	s = pthread_cancel(thr);
	if (s)
		handle_error_en(s, "pthread_cancel");

	/* Join with thread to see what its exit status was */
	s = pthread_join(thr, &res);
	if (s)
		handle_error_en(s, "pthread_join");

	if (res == PTHREAD_CANCELED)
		printf("main(): thread was canceled\n");
	else
		printf("main(): thread wasn't canceled (shouldn't happen!)\n");

	return EXIT_SUCCESS;
}
#endif

#if 0
pthread_cond_t cond;

void *func(void *arg)
{
	(void)arg;

	sleep(2);
	printf("sending signal\n");
	if (pthread_cond_signal(&cond)) {
		printf("%s\n", strerror(errno));
	}
	perror("error: \n");

	return NULL;
}

int main(void)
{
	pthread_t tid;
	struct timespec t;
	pthread_mutex_t mutex;

	if (pthread_mutex_init(&mutex, NULL)) {
		perror("pthread_mutex_init() error\n");
		exit(-1);
	}

	if (pthread_cond_init(&cond, NULL)) {
		perror("pthread_cond_init() error\n");
		exit(-1);
	}

	if (pthread_mutex_lock(&mutex)) {
		perror("pthread_mutex_lock() error\n");
		exit(-1);
	}

	pthread_create(&tid, NULL, func, NULL);

	t.tv_sec = time(NULL) + 1;
	printf("Start\n");
	pthread_cond_timedwait(&cond, &mutex, &t);
	printf("End\n");

	sleep(4);

	printf("Done\n");

	return 0;
}
#endif

#if 0
#define _OPEN_THREADS

static int footprint;

void fun(void *ptr)
{
	printf("%s: Addr->%p\n", __func__, ptr);

	free(ptr);
}

void *thread(void *arg)
{
	char *ptr;

	UNUSED(arg);

	if (!(ptr = malloc(8))) {
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}

	printf("%s: Addr->%p\n", __func__, ptr);

	/* Plan to release storage even if thread doesn't exit normally */
	pthread_cleanup_push(fun, ptr);

	printf("thread has got memory & is waiting to be cancelled\n");
	while (++footprint) {
		sleep(1);
	}

	pthread_cleanup_pop(1);

	return NULL;
}

int main(void)
{
	pthread_t thid;

	if (pthread_create(&thid, NULL, thread, NULL) != 0) {
		perror("pthread_create() error");
		return EXIT_FAILURE;
	}

	while (!footprint)
		sleep(1);

	puts("IPT is cancelling thread\n");

	if (pthread_cancel(thid)) {
		perror("pthread_cancel() error");
		return EXIT_FAILURE;
	}

	if (pthread_join(thid, NULL)) {
		perror("pthread_join() error");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
#endif

#if 0
typedef void (*TimerCb)(void);
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

#if 0
TimerCb gCb;

void f(TimerCb cbfunc)
{
	gCb = cbfunc;
}

void test(void)
{
	printf("Hello World!!!\n");
	pthread_cond_signal(&cond1);
}
#endif

void catcher(int signum)
{
	printf("Inside %s...\n", __func__);
	pthread_cond_signal(&cond1);
}

void timestamp(void)
{
	time_t t;

	time(&t);
	printf("The time is: %s\n", ctime(&t));
}

int _main(void)
{
	struct sigaction sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_handler = catcher;
	sigaction(SIGALRM, &sigact, NULL);

	alarm(3);
	printf("Before pause...%d\n", getpid());;
	timestamp();
	pause();
	printf("After pause...\n");
	timestamp();

	return 0;
}

void *foo(void *arg)
{
	(void)arg;

	printf("Staring thread\n");

	pthread_mutex_lock(&lock);

	printf("Waiting on condition variable cond1\n");
	pthread_cond_wait(&cond1, &lock);

	pthread_mutex_unlock(&lock);

	printf("Returning thread\n");

	return NULL;
}

int main(void)
{
	pthread_t tid1;

	//f(test);

	pthread_create(&tid1, NULL, foo, NULL);

	_main();

	sleep(1);
	//gCb();

	pthread_join(tid1, NULL);

	return 0;
}
#endif

#if 0
#define SIGNAL		SIGTERM

static volatile bool flg;

void sig_hdlr(int num)
{
	UNUSED(num);

	printf("Caught: %d\n", num);
	flg = true;
}

void *func(void *parm)
{
	bool thnum;

	UNUSED(parm);

	printf("%s +\n", __func__);

	thnum = *(int *)parm;

	signal(SIGNAL, sig_hdlr);

	while (!flg) {
		printf("Thread %d running\n", thnum);
		sleep(1);
	}

	printf("%s -\n", __func__);

	pthread_exit((void *)&flg);

	return NULL;
}

int main(void)
{
	int ret;
	pthread_t tid;

	printf("%s +\n", __func__);

	ret = pthread_create(&tid, NULL, func, (void *)&flg);
	if (ret < 0) {
		perror("pthread_create failed\n");
		return EXIT_FAILURE;
	}

	sleep(1);

	ret = pthread_kill(tid, SIGNAL);
	if (ret < 0) {
		perror("pthread_kill failed\n");
		return EXIT_FAILURE;
	}

	while (true) {
		int *tret = NULL;

		printf("%s: sleeping for a second\n", __func__);
		sleep(1);

		printf("%s: trying to join the thread\n", __func__);
		ret = pthread_join(tid, (void **)&tret);
		if (!ret) {
			printf("%s: pthread_join success(%d)\n", __func__, *tret);
			break;
		}

		perror("pthread_join failed\n");
	}

	printf("%s -\n", __func__);

	return EXIT_SUCCESS;
}
#endif

#if 0
pthread_t tid[2] = {0};

void *doSomeThing(void *arg)
{
	(void)arg;
	pthread_t id = pthread_self();

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	printf("\nThread->%d processing\n", pthread_equal(id, tid[0]) ? 1 : 2);

	sleep(3);

	/* Should never reach here */
	printf("%s: -\n", __func__);

	return NULL;
}

int main(void)
{
	int i;

	for (i = 0; i < 1; i++) {
		if (pthread_create(&tid[i], NULL, doSomeThing, NULL))
			perror("pthread_create\n");
	}

	sleep(1);

	if (pthread_cancel(tid[0]))
		perror("pthread_cancel\n");

	if (pthread_join(tid[0], NULL))
		perror("pthread_join\n");

	printf("%s: -\n", __func__);

	return EXIT_SUCCESS;
}
#endif
