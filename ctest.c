#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>

static char **genv;
static char **gargv;
static int32_t gargc;

static void print_argv_envs(void)
{
	int32_t i;

	for (i = 0; i < gargc; i++)
		printf("argv[%d] --> %s\n", i, gargv[i]);

	for (i = 0; genv[i]; i++)
		printf("env[%d] --> %s\n", i, genv[i]);

	printf("\n");
}

static void fun(void)
{
	int32_t fd;
	int32_t ret;
	char buf[32];

#define FNAME		"/dev/ttyS0"
//#define USE_FCNTL
#define USE_SELECT

	fd = open(FNAME, O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "open %s error\n", FNAME);
		return;
	}

#if defined(USE_FCNTL) && !defined(USE_SELECT)
	int32_t flgs;
	
	flgs = fcntl(fd, F_GETFL, 0);
	if (flgs < 0) {
		fprintf(stderr, "fcntl get error\n");
		return;
	}
	
	flgs = fcntl(fd, F_SETFL, flgs | O_NONBLOCK);
	if (flgs < 0) {
		fprintf(stderr, "fcntl set error\n");
		return;
	}

	ret = read(fd, buf, sizeof(buf));
	if (ret < 0) {
		fprintf(stderr, "read %s error\n", FNAME);
		return;
	}
#endif	/*! USE_FCNTL && !USE_SELECT */

#if defined(USE_SELECT) && !defined(USE_FCNTL)
	fd_set set;
	struct timeval t_out;
	
	FD_ZERO(&set);
	FD_SET(fd, &set);

	t_out.tv_sec = 3;
	t_out.tv_usec = 0;

	ret = select(fd + 1, &set, NULL, NULL, &t_out);
	if (ret < 0) {
		fprintf(stderr, "select error\n");
		return;
	} else if (!ret) {
		printf("select timeout\n");
		return;
	} else if (read(fd, buf, sizeof(buf)) < 0) {
		fprintf(stderr, "read %s error\n", FNAME);
		return;
	}

	printf("read from %s success\n", FNAME); 
#endif	/*! USE_SELECT && !USE_FCNTL */

#if defined(USE_SELECT) || defined(USE_FCNTL)
	close(fd);
#endif	/*! USE_SELECT || USE_FCNTL */
}

int main(int32_t argc, char **argv, char **env)
{
	genv = env;
	gargc = argc;
	gargv = argv;

	fun();

	return EXIT_SUCCESS;
}
