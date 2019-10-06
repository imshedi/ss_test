#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>

#define UNUSED(var) ((void)(var))

#if 0
/* Usage example
 *
 * First, compile and run this program:
 *     $ gcc signal.c
 *     $ ./a.out
 *
 * It will print out its pid. Use it from another terminal to send signals
 *     $ kill -HUP <pid>
 *     $ kill -USR1 <pid>
 *     $ kill -ALRM <pid>
 *
 * Exit the process with ^C ( = SIGINT) or SIGKILL, SIGTERM
 */

void handle_sigalrm(int signal)
{
	if (signal != SIGALRM)
		fprintf(stderr, "Caught wrong signal: %d\n", signal);

	printf("Got sigalrm, do_sleep() will end\n");
}

void do_sleep(int seconds)
{
	struct sigaction sa;
	sigset_t mask;

	sa.sa_handler = &handle_sigalrm; // Intercept and ignore SIGALRM
	sa.sa_flags = SA_RESETHAND; // Remove the handler after first signal
	sigfillset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL);

	// Get the current signal mask
	sigprocmask(0, NULL, &mask);

	// Unblock SIGALRM
	sigdelset(&mask, SIGALRM);

	// Wait with this mask
	alarm(seconds);
	sigsuspend(&mask);

	printf("sigsuspend() returned\n");
}

void handle_signal(int signal)
{
	/*
	 * Please note that printf et al. are NOT safe to use in signal handlers.
	 * Look for async safe functions.
	 */
	const char *signal_name;
	sigset_t pending;

	// Find out which signal we're handling
	switch (signal) {
        case SIGHUP:
                signal_name = "SIGHUP";
                break;
        case SIGUSR1:
                signal_name = "SIGUSR1";
                break;
        case SIGINT:
                printf("Caught SIGINT, exiting now\n");
                exit(0);
        default:
                fprintf(stderr, "Caught wrong signal: %d\n", signal);
                return;
	}

	printf("Caught %s, sleeping for ~3 seconds\n"
			"Try sending another SIGHUP / SIGINT / SIGALRM "
			"(or more) meanwhile\n", signal_name);
	/*
	 * Indeed, all signals are blocked during this handler
	 * But, at least on OSX, if you send 2 other SIGHUP,
	 * only one will be delivered: signals are not queued
	 * However, if you send HUP, INT, HUP,
	 * you'll see that both INT and HUP are queued
	 * Even more, on my system, HUP has priority over INT
	 */
	do_sleep(3);
	printf("Done sleeping for %s\n", signal_name);

	// So what did you send me while I was asleep?
	sigpending(&pending);
	if (sigismember(&pending, SIGHUP))
		printf("A SIGHUP is waiting\n");

	if (sigismember(&pending, SIGUSR1))
		printf("A SIGUSR1 is waiting\n");

	printf("Done handling %s\n\n", signal_name);
}

int main(void)
{
	struct sigaction sa;

	// Print pid, so that we can send signals from other shells
	printf("My pid is: %d\n", getpid());

	// Setup the sighub handler
	sa.sa_handler = &handle_signal;

	// Restart the system call, if at all possible
	sa.sa_flags = SA_RESTART;

	// Block every signal during the handler
	sigfillset(&sa.sa_mask);

	// Intercept SIGHUP and SIGINT
	if (sigaction(SIGHUP, &sa, NULL) == -1)
		perror("Error: cannot handle SIGHUP"); // Should not happen

	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		perror("Error: cannot handle SIGUSR1"); // Should not happen

	// Will always fail, SIGKILL is intended to force kill your process
	if (sigaction(SIGKILL, &sa, NULL) == -1) {
		perror("Cannot handle SIGKILL"); // Will always happen
		printf("You can never handle SIGKILL anyway...\n");
	}

	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGINT"); // Should not happen

	for (;;) {
		printf("\nSleeping for ~3 seconds\n");
		do_sleep(3); // Later to be replaced with a SIGALRM
	}
}
#endif

#if 0
void catcher(int signum)
{
	UNUSED(signum);
	printf("%s: has gained control\n", __func__);
}

int main(int argc, char **argv)
{
	sigset_t sigset;
	struct sigaction sact;

	UNUSED(argv);
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
	sact.sa_handler = catcher;
	sigaction(SIGTERM, &sact, NULL);

	sigfillset(&sigset);
	sigprocmask(SIG_SETMASK, &sigset, NULL);

	puts("before kill\n");
	kill(getpid(), SIGTERM);
	puts("after kill\n");

	if (argc > 1) {
		puts("before unblocking SIGTERM\n");
		sigdelset(&sigset, SIGTERM);
		sigprocmask(SIG_SETMASK, &sigset, NULL);
		puts("after unblocking SIGTERM\n");
	}

	return 0;
}
#endif

#if 1
/* setitimer simple use of the interval timer */

#define INTERVAL 3000	/* number of milliseconds to go off */

void DoStuff(void)
{
	printf("\nTimer went off\n");
	system("date");
}

int main(void)
{
	struct itimerval it_val;	/* for setting itimer */

	/*
	 * Upon SIGALRM, call DoStuff().
	 * Set interval timer. We want frequency in ms, but the setitimer call needs
	 * seconds and useconds.
	 */
	if (signal(SIGALRM, (void (*)(int))DoStuff) == SIG_ERR) {
		perror("Unable to catch SIGALRM");
		exit(1);
	}

	it_val.it_value.tv_sec = INTERVAL / 1000;
	it_val.it_value.tv_usec = (INTERVAL * 1000) % 1000000;
	it_val.it_interval = it_val.it_value;
	if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
		perror("\nerror calling setitimer\n");
		exit(1);
	}

	while (1)
		pause();
}
#endif

#if 0
void catcher(int signum)
{
	UNUSED(signum);
	printf("catcher() has received signal: %d\n", signum);
}

int main(void)
{
	sigset_t sigset;
	struct sigaction sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
	sact.sa_handler = catcher;
	sigaction(SIGUSR1, &sact, NULL);
	sigaction(SIGKILL, &sact, NULL);
	sigaction(SIGSTOP, &sact, NULL);
	sigaction(SIGINT, &sact, NULL);

	sigfillset(&sigset);
	sigprocmask(SIG_SETMASK, &sigset, NULL);

	puts("before kill()\n");
	kill(getpid(), SIGINT);

	puts("before unblocking SIGUSR1\n");

	sigdelset(&sigset, SIGUSR1);
	sigdelset(&sigset, SIGKILL);
	sigdelset(&sigset, SIGSTOP);
	sigdelset(&sigset, SIGINT);

	sigprocmask(SIG_SETMASK, &sigset, NULL);
	puts("after unblocking SIGUSR1\n");

	while (1)
		sleep(1);

	return 0;
}
#endif

#if 0
void catcher(int signum)
{
	printf("Inside %s...\n", __func__);
}

void timestamp(void)
{
	time_t t;

	time(&t);
	printf("The time is: %s\n", ctime(&t));
}

int main(void)
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
#endif
