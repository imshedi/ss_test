#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

static bool cond = false;

void catcher(int signum)
{
	cond = true;
	printf("%s: Caught SIGINT(%d)\n", __func__, signum);
}

int main(void)
{
	printf("%s: +\n", __func__);

	if (signal(SIGINT, catcher) == SIG_ERR) {
		fprintf(stderr, "Unable to register handler for SIGINT\n");
		return -1;
	}

	while (!cond) {
		printf("Break condition is not set yet\n");
		sleep(1);
	}

	printf("%s: -\n", __func__);

	return 0;
}
